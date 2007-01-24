#include <cul/cul_arg.h>

#include <cul/cul_base_char.h>
#include <cul/cul_base_ptr.h>
#include <cul/cul_string_raw.h>

/* private CulArg functions */
CulArg *cul_arg_next(CulArg *t);
CulArg *cul_arg_next_option(CulArg *t);
CulArg *cul_arg_next_group(CulArg *t);

/* private data types */
typedef enum _CulArgType CulArgType;
enum _CulArgType {
	CUL_ARG_TYPE_UNK,
	CUL_ARG_TYPE_SHORT,
	CUL_ARG_TYPE_LONG,
	CUL_ARG_TYPE_END
};

/* private command line functions */
static inline void cul_arg_cmd_next(int *argc, char ***argv);
CulArgType cul_arg_cmd_type(const char *arg);

cul_errno cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table);
cul_errno cul_arg_cmd_parse_long(int *argc, char ***argv, CulArg *table);
cul_bool cul_arg_cmd_convert(const char *arg, CulArg *t);

/* Find and return next valid argument description, from argument table */
CulArg *cul_arg_next(CulArg *t) {
	if( (++t)->flags == CUL_ARG_END )
		return NULL;
	return t;
}

/* Find and return next option, short or long, from argument table */
CulArg *cul_arg_next_option(CulArg *t) {
	while( t ) {
		switch( (++t)->flags & ~CUL_ARG_MASK ) {
			case CUL_ARG_END:
				return NULL;
			case CUL_ARG_HELP:
			case CUL_ARG_GROUP:
				continue;
			default:
				break;
		}
		break;
	}
	return t;
}

/* Find and return next group from argument table */
CulArg *cul_arg_next_group(CulArg *t) {
	while( t ) {
		switch( (++t)->flags & ~CUL_ARG_MASK ) {
			case CUL_ARG_END:
				return NULL;
			case CUL_ARG_GROUP:
				break;
			default:
				continue;
		}
		break;
	}
	return t;
}

/* Find and return specific short argument in argument table */
CulArg *cul_arg_search_short(CulArg *t, char arg) {
	while( t ) {
		if( t->short_name == arg )
			break;
		t = cul_arg_next_option(t);
	}
	return t;
}

/* Find and return specific long argument in argument table */
CulArg *cul_arg_search_long(CulArg *t, const char *arg) {
	const char *pos;
	size_t length;

	if( (pos = cul_strchr(arg,'=')) )
		length = pos - arg;
	else
		length = cul_strlen(arg);

	while( t ) {
		if( t->long_name && (!cul_strncmp(arg, t->long_name, length) && cul_strisnull(t->long_name + length)) )
			break;
		t = cul_arg_next_option(t);
	}
	return t;
}

static inline void cul_arg_cmd_next(int *argc, char ***argv) {
	--(*argc);
	++(*argv);
}

CulArgType cul_arg_cmd_type(const char *arg) {
	if( *arg == '-' ) {
		if( *(arg + 1) == '-' )
			if( *(arg + 2) )
				return CUL_ARG_TYPE_LONG;
			else
				return CUL_ARG_TYPE_END;
		else
			return CUL_ARG_TYPE_SHORT;
	}
	return CUL_ARG_TYPE_UNK;
}

cul_errno cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table) {
	const char *arg_string = **argv + 1;
	cul_bool is_multi_flag = CUL_FALSE;
	CulArg *t;

	while( *arg_string ) {
		/* find entry in options table */
		if( !(t = cul_arg_search_short(table, *arg_string)) )
			return CUL_EARGUNK;

		const CulArgFlag flag = (t->flags & CUL_ARG_MASK);
		const cul_bool is_option_bool = (flag == CUL_ARG_BOOL);

		/* we have more flags than one */
		if( is_multi_flag ) {
			if( !is_option_bool )
				return CUL_EARGSHORT;

			/* convert flag option */
			if( cul_arg_cmd_convert(arg_string, t) )
				t->flags |= CUL_ARG_FOUND;
			else
				return CUL_EARGCONV;

			/* end of multiple bool short flags */
			if( cul_strisnull(++arg_string) ) {
				cul_arg_cmd_next(argc, argv);
				return CUL_SUCCESS;
			}
		}
		/* this is first flag */
		else {
			size_t size;

			/* if not bool we have to move to flag option */
			if( !is_option_bool ) {
				/* check if there is something after flag */
				if( !cul_strisnull(arg_string+1) ) {
					/* option is right after flag */
					++arg_string;
					size = 1;
				}
				else {
					/* option is a separate argument */

					/* check if we have more arguments present */
					if( *argc < 2 )
						return CUL_EARGCONV;

					arg_string = *(*argv + 1);
					size = 2;
				}
			}
			else {
				/* this is first of possible multiple bool options */

				/* check if we have more flags */
				if( !cul_strisnull(++arg_string) )
					is_multi_flag = CUL_TRUE;

				/* do not move to next arguments */
				size = 0;
			}

			/* convert flag option */
			if( cul_arg_cmd_convert(arg_string, t) )
				t->flags |= CUL_ARG_FOUND;
			else
				return CUL_EARGCONV;

			if( size > 0 ) {
				/* move to next argument */
				while( size-- > 0 )
					cul_arg_cmd_next(argc, argv);

				return CUL_SUCCESS;
			}
		}
	}
	return CUL_EARGSHORT;
}

cul_errno cul_arg_cmd_parse_long(int *argc, char ***argv, CulArg *table) {
	const char *arg_string = **argv + 2;
	const char *arg_option = cul_strchr(arg_string, '=');
	CulArg *t;

	/* check if we have option */
	if( *arg_string ) {
		/* find entry in options table */
		if( !(t = cul_arg_search_long(table, arg_string)) )
			return CUL_EARGUNK;

		size_t size;
		const CulArgFlag flag = (t->flags & CUL_ARG_MASK);
		const cul_bool is_option_bool = (flag == CUL_ARG_BOOL);

		/* if not bool we have to move to flag option */
		if( !is_option_bool ) {
			/* check if there is something after flag */
			if( arg_option ) {
				/* option is right after flag */
				++arg_string;
				size = 1;
			}
			else {
				/* option is a separate argument */

				/* check if we have more arguments present */
				if( *argc < 2 )
					return CUL_EARGCONV;

				arg_string = *(*argv + 1);
				size = 2;
			}
		}
		else {
			/* check if there is flag option present */
			if( arg_option )
				return CUL_EARGCONV;

			size = 1;
		}

		/* convert flag option */
		if( cul_arg_cmd_convert(arg_string, t) )
			t->flags |= CUL_ARG_FOUND;
		else
			return CUL_EARGCONV;

		/* move to next argument */
		while( size-- > 0 )
			cul_arg_cmd_next(argc, argv);

		return CUL_SUCCESS;
	}
	return CUL_EARGLONG;
}

cul_bool cul_arg_cmd_convert(const char *arg, CulArg *t) {
	char *end;

	switch( t->flags & CUL_ARG_MASK ) {
		case CUL_ARG_BOOL:
			*((cul_bool *)t->value) = CUL_TRUE;
			return CUL_TRUE;
		case CUL_ARG_INT:
			if( *arg ) {
				long tmp = cul_strtol(arg, &end, 0);
				if( !*end && tmp == (int)tmp ) {
					*((int *)t->value) = (int)tmp;
					return CUL_TRUE;
				}
			}
			break;
		case CUL_ARG_DOUBLE:
			if( *arg ) {
				double tmp = cul_strtod(arg, &end);
				if( !*end ) {
					*((double *)t->value) = tmp;
					return CUL_TRUE;
				}
			}
			break;
		case CUL_ARG_STRING:
			if( *arg ) {
				size_t length = cul_strlen(arg);

				/* allocate string memory */
				char *tmp = cul_cnew(length + 1);
				if( tmp == NULL )
					break;

				/* copy string */
				cul_strcpy(tmp, arg);

				/* free previous string, only if already found */
				if( t->value && (t->flags & CUL_ARG_FOUND) )
					cul_free(*((char **)t->value));
				*((char **)t->value) = tmp;

				return CUL_TRUE;
			}
			break;
		case CUL_ARG_CALLBACK:
			if( *arg && ((cul_arg_callback_f *)(t->value))(arg, t) )
				return CUL_TRUE;
			break;
	}
	return CUL_FALSE;
}

/* Parse program arguments using argument tables */
cul_errno cul_arg_parse(int *argc, char ***argv, CulArg **table) {
	CulArg *t;
	cul_errno result;

  /* omit first parameter */
	cul_arg_cmd_next(argc, argv);

	while( *argc > 0 ) {
		switch( cul_arg_cmd_type(**argv) ) {
			case CUL_ARG_TYPE_LONG:
				result = cul_arg_cmd_parse_long(argc, argv, *table);
				if( result != CUL_SUCCESS )
					return result;

				break;
			case CUL_ARG_TYPE_END:
				break;
			case CUL_ARG_TYPE_SHORT:
				result = cul_arg_cmd_parse_short(argc, argv, *table);
				if( result != CUL_SUCCESS )
					return result;

				break;
			case CUL_ARG_TYPE_UNK:
				return CUL_EARGUNK;
		}
	}
	if( (t = cul_arg_check_required(*table)) != NULL ) {
		*table = t;
		return CUL_EARGMISS;
	}
	return CUL_SUCCESS;
}

/* Print all help string information from table */
void cul_arg_print_help(CulArg *table) {
	CulArg *t = table;
	while( t ) {
		switch( t->flags & ~CUL_ARG_MASK ) {
			case CUL_ARG_HELP:
				cul_printf("%s\n", t->desciption);
				break;
			case CUL_ARG_GROUP:
				if( t != table )
					cul_printf("\n");
				cul_printf("%s\n", t->desciption);
				break;
			default:
				if( t->short_name ) {
					if( t->long_name )
						cul_printf("  -%c, --%-16s  %s\n", t->short_name, t->long_name, t->desciption);
					else
						cul_printf("  -%-21c  %s\n", t->short_name, t->desciption);
				}
				else if( t->long_name )
					cul_printf("  --%-20s  %s\n", t->long_name, t->desciption);
				break;
		}
		t = cul_arg_next(t);
	}
}

/* Check argument table if all required arguments were found */
CulArg *cul_arg_check_required(CulArg *table) {
	while( table ) {
		if( table->flags & CUL_ARG_REQUIRED && !(table->flags & CUL_ARG_FOUND) )
			return table;
		table = cul_arg_next_option(table);
	}
	return NULL;
}

void cul_arg_free(CulArg *table) {
	while( table ) {
		CulArgFlag flag = table->flags;
		if( flag & CUL_ARG_FOUND ) {
			if( flag & CUL_ARG_STRING ) {
				cul_free(*((char **)table->value));
				*((char **)table->value) = NULL;
			}
		}
		table = cul_arg_next_option(table);
	}
}
