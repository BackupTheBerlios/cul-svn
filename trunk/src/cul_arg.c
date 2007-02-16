#include <cul/cul_arg.h>

#include <cul/cul_stream.h>
#include <cul/cul_base_char.h>
#include <cul/cul_base_ptr.h>
#include <cul/cul_str.h>

/* private functions */
CulArg *_cul_arg_next(CulArg *t);
CulArg *_cul_arg_next_option(CulArg *t);

static inline void _cul_arg_cmd_next(int *argc, char ***argv);
cul_errno _cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table);
cul_errno _cul_arg_cmd_parse_long(int *argc, char ***argv, CulArg *table);
cul_bool _cul_arg_cmd_convert(const char *arg, CulArg *t);

/* Parse program arguments using argument tables */
cul_errno cul_arg_parse(int *argc, char ***argv, CulArg **table) {

	/* omit first parameter */
	_cul_arg_cmd_next(argc, argv);

	while( *argc > 0 ) {
		char *arg = **argv;
		cul_errno result;

		if( *arg == '-' ) {
			if( *(++arg) == '-' ) {
				if( cul_strisnull(++arg) )
					/* finish parsing */
					break;

				/* long option */
				result = _cul_arg_cmd_parse_long(argc, argv, *table);
				if( result != CUL_SUCCESS )
					return result;

				/* parse next options */
				continue;
			}
			if( cul_strisnull(arg) )
				return CUL_EARGUNK;

			/* short option */
			result = _cul_arg_cmd_parse_short(argc, argv, *table);
			if( result != CUL_SUCCESS )
				return result;

			/* parse next options */
			continue;
		}
		else
			return CUL_EARGUNK;
	}

	CulArg *t;
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
				cul_printf_stream("%s\n", t->desciption);
				break;
			default:
				if( t->short_name ) {
					if( t->long_name )
						cul_printf_stream("  -%c, --%-16s  %s\n", t->short_name, t->long_name, t->desciption);
					else
						cul_printf_stream("  -%-21c  %s\n", t->short_name, t->desciption);
				}
				else if( t->long_name )
					cul_printf_stream("  --%-20s  %s\n", t->long_name, t->desciption);
				break;
		}
		t = _cul_arg_next(t);
	}
}

void cul_arg_free(CulArg *table) {
	while( table != NULL ) {
		CulArgFlag flag = table->flags;
		if( flag & CUL_ARG_FOUND ) {
			if( flag & CUL_ARG_STRING ) {
				cul_free(*((char **)table->value));
				*((char **)table->value) = NULL;
			}
		}
		table = _cul_arg_next_option(table);
	}
}

/* Check argument table if all required arguments were found */
CulArg *cul_arg_check_required(CulArg *table) {
	while( table != NULL ) {
		if( table->flags & CUL_ARG_REQUIRED && !(table->flags & CUL_ARG_FOUND) )
			return table;
		table = _cul_arg_next_option(table);
	}
	return NULL;
}

/* Find and return specific short argument in argument table */
CulArg *cul_arg_search_short(CulArg *t, char arg) {
	while( t != NULL ) {
		if( t->short_name == arg )
			break;
		t = _cul_arg_next_option(t);
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

	while( t != NULL ) {
		if( t->long_name != NULL &&
				( !cul_strncmp(arg, t->long_name, length) &&
				cul_strisnull(t->long_name + length)) )
			break;
		t = _cul_arg_next_option(t);
	}
	return t;
}

/* Find and return next valid argument description, from argument table */
CulArg *_cul_arg_next(CulArg *t) {
	if( (++t)->flags & CUL_ARG_END ) {
		if( t->flags & CUL_ARG_JOIN )
			t = t->value;
		else
			return NULL;
	}
	return t;
}

/* Find and return next option, short or long, from argument table */
CulArg *_cul_arg_next_option(CulArg *t) {
	while( t != NULL ) {
		switch( (++t)->flags & ~CUL_ARG_MASK ) {
			case CUL_ARG_END:
				return NULL;
			case CUL_ARG_JOIN:
			case CUL_ARG_END|CUL_ARG_JOIN:
				t = t->value;
				continue;
			case CUL_ARG_HELP:
				continue;
			default:
				break;
		}
		break;
	}
	return t;
}

static inline void _cul_arg_cmd_next(int *argc, char ***argv) {
	--(*argc);
	++(*argv);
}

cul_errno _cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table) {
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
			if( _cul_arg_cmd_convert(arg_string, t) )
				t->flags |= CUL_ARG_FOUND;
			else
				return CUL_EARGCONV;

			/* end of multiple bool short flags */
			if( cul_strisnull(++arg_string) ) {
				_cul_arg_cmd_next(argc, argv);
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
			if( _cul_arg_cmd_convert(arg_string, t) )
				t->flags |= CUL_ARG_FOUND;
			else
				return CUL_EARGCONV;

			if( size > 0 ) {
				/* move to next argument */
				while( size-- > 0 )
					_cul_arg_cmd_next(argc, argv);

				return CUL_SUCCESS;
			}
		}
	}
	return CUL_EARGSHORT;
}

cul_errno _cul_arg_cmd_parse_long(int *argc, char ***argv, CulArg *table) {
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
				arg_string = arg_option+1;
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
		if( _cul_arg_cmd_convert(arg_string, t) )
			t->flags |= CUL_ARG_FOUND;
		else
			return CUL_EARGCONV;

		/* move to next argument */
		while( size-- > 0 )
			_cul_arg_cmd_next(argc, argv);

		return CUL_SUCCESS;
	}
	return CUL_EARGLONG;
}

cul_bool _cul_arg_cmd_convert(const char *arg, CulArg *t) {
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
