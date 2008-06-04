#include <cul/cul_arg.h>
#include <cul/cul_stream.h>
#include <cul/cul_str.h>
#include <cul/cul_slist.h>

#include <stdlib.h>
#include <string.h>

/* global list to control auto CulArg memory management */
static CulSList *cul_arg_auto = NULL;

static void cul_arg_finalize(void) __attribute__ ((destructor));
static void cul_arg_finalize(void) {
	cul_slist_free_all(cul_arg_auto, CUL_FREE_F(cul_arg_free));
}

/* argument parser context */
typedef struct _CulArgContext {
	CulArg *table;     /* argument table */

	/* command line arguments */
	int argc;          /* number of remaining arguments to parse */
	int argn;          /* number of remaining arguments NOT to parse */
	char **argv;       /* remaining arguments */

	/* selected argument table entries */
	CulArg *current; /* current argument entry */
	CulArg *last;    /* last argument entry */

	/* other properties */
	size_t position;   /* current argument position */
} _CulArgContext;

/* private functions */
static CulArg          *_cul_arg_find_short     (const CulArg *table, char value);
static CulArg          *_cul_arg_find_long      (const CulArg *table, const char *value);
static CulArg          *_cul_arg_process_ex     (CulArg *table);
static CulArg          *_cul_arg_process_need   (CulArg *table);

static inline void      _cul_arg_cmd_next       (_CulArgContext *context);
static cul_errno        _cul_arg_cmd_parse_short(_CulArgContext *context);
static cul_errno        _cul_arg_cmd_parse_long (_CulArgContext *context);
static cul_errno        _cul_arg_cmd_parse_none (_CulArgContext *context);

static cul_bool         _cul_arg_cmd_convert    (const char *arg, CulArg *entry, size_t *position);
static inline cul_bool  _cul_arg_flag_is_switch (CulArgFlag flag);
static inline cul_bool  _cul_arg_flag_is_found  (CulArgFlag flag);

/* Parse program arguments using argument tables */
cul_errno cul_arg_parse(int *argc, char ***argv, CulArg **table) {
	_CulArgContext context;

	/* initialize context */
	memset(&context, 0, sizeof(_CulArgContext));
	context.table = *table;
	context.argc = *argc;
	context.argv = *argv;

	/* omit first non important argument */
	_cul_arg_cmd_next(&context);

	while( context.argc > 0 ) {
		cul_errno error = CUL_SUCCESS;

		/* parse current string in context */
		if( (*context.argv)[0] == '-' ) {
			if( (*context.argv)[1] == '-' ) {
				if( (*context.argv)[2] == '\0' )             /* '--' */ /* stop parsing */
					break;
				else                                         /* '--.*' */ /* long switch */
					error = _cul_arg_cmd_parse_long(&context);
			} else if( (*context.argv)[1] == '\0' )        /* '-' */ /* error */
				error = CUL_EARGUNK;
			else                                           /* '-.*' */ /* short switch */
			error = _cul_arg_cmd_parse_short(&context);
		} else                                           /* '.*' */ /* not switch */
			error = _cul_arg_cmd_parse_none(&context);

		/* evaluate result */
		if( error ) {
			*table = context.table;
			*argc = context.argc + context.argn;
			*argv = context.argv;

			switch( error ) {
			case CUL_EARGCONV: return CUL_EARGCONV;
			case CUL_EARGUNK:  return CUL_EARGUNK;
			default:           return CUL_UNKNOWN;
			}
		}
	}

	/* finalize context arguments */
	*argc = context.argn;
	*argv = context.argv;

	/* check required flags in argument table */
	if( (*table = _cul_arg_process_ex(context.table)) != NULL )
		return CUL_EARGEX;
	if( (*table = _cul_arg_process_need(context.table)) != NULL )
		return CUL_EARGNEED;

	/* finalize context argument table */
	*table = context.table;

	return CUL_SUCCESS;
}

cul_errno cul_arg_parse_auto(int *argc, char ***argv, CulArg **table) {
	/* automatically manage CulArg table memory */
	cul_arg_auto = cul_slist_insert_prev(cul_arg_auto, *table);
	return cul_arg_parse(argc, argv, table);
}

void cul_arg_print_default(const CulArg *table) {
	for(const CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END:
			t = t->value;
			break;
		case CUL_ARG_PRINT:
			fprintf(cul_stream_get(), "%s\n", t->description);
			t += 1;
			break;
		default:
			if( t->long_name && t->short_name )
				fprintf(cul_stream_get(),"  -%c, --%-16s  %s\n",
				        t->short_name, t->long_name, t->description);
			else if( t->long_name )
				fprintf(cul_stream_get(), "  --%-20s  %s\n",
				        t->long_name, t->description);
			else if( t->short_name )
				fprintf(cul_stream_get(),"  -%-21c  %s\n",
				        t->short_name, t->description);
			t += 1;
			break;
		}
	}
}

void cul_arg_free(CulArg *table) {
	/* cache table */
	for(CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END:   t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( t->flags & CUL_ARG_FOUND ) {
				switch( t->flags & CUL_ARG_INPUT_MASK ) {
				case CUL_ARG_STR:
					free(*(char **)t->value);
					t->value = NULL;
					break;
				case CUL_ARG_STRV:
					cul_strv_free(*(char ***)t->value);
					t->value = NULL;
					break;
				default:
					break;
				}
			}
			t += 1;
			break;
		}
	}
}

void cul_arg_connect(CulArg *table, CulArg *other) {
	/* check if connection is possible or make any sense */
	if( table == NULL || other == NULL )
		return;

	/* find end of table */
	for(; !(table->flags & CUL_ARG_END); table += 1) ;

	/* find last end of table */
	while( table->value != NULL )
		for(table = table->value; !(table->flags & CUL_ARG_END); table += 1) ;

	/* connect tables */
	table->value = other;
}

cul_bool cul_arg_after(const CulArg *table, const CulArg *other) {
	const size_t table_position = CUL_ARG_FLAG_POS(table->flags);
	const size_t other_position = CUL_ARG_FLAG_POS(other->flags);

	return table_position > other_position;
}

cul_bool cul_arg_before(const CulArg *table, const CulArg *other) {
	return cul_arg_after(other, table);
}

static CulArg *_cul_arg_find_short(const CulArg *table, char value) {
	for(const CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END: t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( t->short_name == value )
				return (CulArg *)t;
			t += 1;
			break;
		}
	}
	return NULL;
}

static CulArg *_cul_arg_find_long(const CulArg *table, const char *value) {
	const char *str = strchr(value, '=');
	const size_t len = (str == NULL)? strlen(value): (size_t)(str - value);

	for(const CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END: t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( t->long_name != NULL &&
					strncmp(value, t->long_name, len) == 0 &&
					t->long_name[len] == '\0' )
				return (CulArg *)t;
			t += 1;
			break;
		}
	}
	return NULL;
}

static CulArg *_cul_arg_process_ex(CulArg *table) {
	const size_t size = (CUL_ARG_EX_MASK >> CUL_ARG_EX_SHIFT) + 1;
	cul_bool is_ex_found[size];

	for(size_t i = 0; i < size; ++i)
		is_ex_found[i] = CUL_FALSE;

	/* initialize EX flags */
	for(CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END:   t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( (t->flags & CUL_ARG_EX) && (t->flags & CUL_ARG_FOUND) ) {
				const size_t index = CUL_ARG_FLAG_EX(t->flags);

				/* check if EX was already found */
				if( is_ex_found[index] )
					return t;

				/* modify EX found state */
				is_ex_found[index] = CUL_TRUE;
			}

			t += 1;
			break;
		}
	}

	/* extend FOUND flag for each EX item */
	for(CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END:   t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( (t->flags & CUL_ARG_EX) && is_ex_found[ CUL_ARG_FLAG_EX(t->flags) ] )
				t->flags |= CUL_ARG_FOUND;
			t += 1;
			break;
		}
	}

	return NULL;
}

static CulArg *_cul_arg_process_need(CulArg *table) {
	/* check for NEED arguments */
	for(CulArg *t = table; t != NULL; ) {
		switch( t->flags & CUL_ARG_TYPE_MASK ) {
		case CUL_ARG_END:   t = t->value; break;
		case CUL_ARG_PRINT: t += 1; break;
		default:
			if( (t->flags & CUL_ARG_NEED) && !(t->flags & CUL_ARG_FOUND) )
				return t;

			t += 1;
			break;
		}
	}
	return NULL;
}

static inline void _cul_arg_cmd_next(_CulArgContext *context) {
	context->argc -= 1;
	context->argv += 1;
}

static cul_errno _cul_arg_cmd_parse_short(_CulArgContext *context) {
	const char *arg = *context->argv + 1;
	cul_bool is_switch, is_multi_flag = CUL_FALSE;
	CulArg *entry;

	while( *arg ) {
		/* find entry in options table */
		if( !(entry = _cul_arg_find_short(context->table, *arg)) )
			return CUL_EARGUNK;

		/* check flag type */
		is_switch = _cul_arg_flag_is_switch(entry->flags);

		/* we have more flags than one */
		if( is_multi_flag ) {
			if( !is_switch )
				return CUL_EARGCONV;

			/* convert flag option */
			if( !_cul_arg_cmd_convert(arg, entry, &context->position) )
				return CUL_EARGCONV;

			/* end of multiple bool short flags */
			if( *(++arg) == '\0' ) {
				_cul_arg_cmd_next(context);
				return CUL_SUCCESS;
			}
		/* this is first flag */
		} else {
			/* number of arguments to skip */
			size_t size;

			/* if not switch we have to move to flag option */
			if( !is_switch ) {
				/* check if there is something after flag */
				if( *(arg+1) != '\0' ) {
					/* option is right after flag */
					++arg;
					size = 1;
				} else {
					/* option is a separate argument */

					/* check if we have more arguments present */
					if( context->argc < 2 )
						return CUL_EARGCONV;

					arg = *(context->argv + 1);
					size = 2;
				}
			/* this is first of possible multiple switch options */
			} else {

				/* check if we have more flags */
				if( *(++arg) != '\0' ) {
					is_multi_flag = CUL_TRUE;
					size = 0;
				} else
					size = 1;
			}

			/* convert flag option */
			if( !_cul_arg_cmd_convert(arg, entry, &context->position) )
				return CUL_EARGCONV;

			if( size > 0 ) {
				/* move to next argument */
				while( size-- > 0 )
					_cul_arg_cmd_next(context);

				return CUL_SUCCESS;
			}
		}
	}
	return CUL_EFAILED;
}

static cul_errno _cul_arg_cmd_parse_long(_CulArgContext *context) {
	const char *arg = *context->argv + 2;
	const char *arg_option = strchr(arg, '=');
	cul_bool is_switch;
	CulArg *entry;

	/* check if we have option */
	if( *arg ) {
		/* find entry in options table */
		if( !(entry = _cul_arg_find_long(context->table, arg)) )
			return CUL_EARGUNK;

		/* check flag type */
		is_switch = _cul_arg_flag_is_switch(entry->flags);

		/* number positions to skip */
		size_t size = 0;

		/* if not bool we have to move to flag option */
		if( !is_switch ) {
			/* check if there is something after flag */
			if( arg_option ) {
				/* option is right after flag */
				arg = arg_option + 1;
				size = 1;
			} else {
				/* option is a separate argument */

				/* check if we have more arguments present */
				if( context->argc < 2 )
					return CUL_EARGCONV;

				arg = *(context->argv + 1);
				size = 2;
			}
		} else {
			/* check if there is flag option present */
			if( arg_option )
				return CUL_EARGCONV;

			size = 1;
		}

		/* convert flag option */
		if( !_cul_arg_cmd_convert(arg, entry, &context->position) )
			return CUL_EARGCONV;

		/* move to next argument */
		while( size-- > 0 )
			_cul_arg_cmd_next(context);

		return CUL_SUCCESS;
	}
	return CUL_EFAILED;
}

static cul_errno _cul_arg_cmd_parse_none(_CulArgContext *context) {
	CUL_UNUSED(context);
	return CUL_EFAILED;
}

static cul_bool _cul_arg_cmd_convert(const char *arg, CulArg *entry, size_t *position) {
	switch( entry->flags & CUL_ARG_INPUT_MASK ) {
	case CUL_ARG_TRUE:
		*((cul_bool *)entry->value) = CUL_TRUE;
		break;
	case CUL_ARG_FALSE:
		*((cul_bool *)entry->value) = CUL_FALSE;
		break;
	case CUL_ARG_COUNT:
		*((int *)entry->value) += 1;
		break;
	case CUL_ARG_INT:
		if( *arg ) if( !cul_strtoi(arg, 0, entry->value) )
			break;
		return CUL_FALSE;
	case CUL_ARG_DOUBLE:
		if( *arg ) if( !cul_strtod(arg, entry->value) )
			break;
		return CUL_FALSE;
	case CUL_ARG_STR:
		if( *arg ) {
			char *tmp = cul_strdup(arg);
			if( tmp != NULL ) {
				/* free old value, if already found */
				if( _cul_arg_flag_is_found(entry->flags) )
					free(*(char **)entry->value);
				*(char **)entry->value = tmp;
				break;
			}
		}
		return CUL_FALSE;
	case CUL_ARG_STRV:
		if( *arg ) {
			char *tmp, **tmpv;
			size_t size;

			/* initialize current state  */
			if( _cul_arg_flag_is_found(entry->flags) )
				size = cul_strv_size(*(char ***)entry->value);
			else
				size = 0;

			/* allocate all needed space */
			tmp = cul_strdup(arg);
			tmpv = cul_strv_new(size + 1);

			if( tmp != NULL && tmpv != NULL ) {
				/* copy all old strings to tmpv (only pointers) */
				char **strv = *(char ***)entry->value;
				for(size_t i = 0; i < size; ++i)
					tmpv[i] = strv[i];

				/* add new string and NULL end */
				tmpv[size] = tmp;
				tmpv[size+1] = NULL;

				/* free old value, if already found (only strv pointer) */
				if( _cul_arg_flag_is_found(entry->flags) )
					free(*(char ***)entry->value);
				*(char ***)entry->value = tmpv;

				break;
			}

			/* free allocated memory if present */
			free(tmp);
			free(tmpv);
		}
		return CUL_FALSE;
	default:
		return CUL_FALSE;
	}

	/* mark flag as found */
	entry->flags |= CUL_ARG_FOUND;

	/* clear and set position */
	entry->flags &= ~CUL_ARG_POS_MASK;
	entry->flags |= (*position)++ << 12;

	return CUL_TRUE;
}

static inline cul_bool _cul_arg_flag_is_switch(CulArgFlag flag) {
	switch( flag & CUL_ARG_INPUT_MASK ) {
	case CUL_ARG_TRUE:
	case CUL_ARG_FALSE:
	case CUL_ARG_COUNT: return CUL_TRUE;
	default:            return CUL_FALSE;
	}
}

static inline cul_bool _cul_arg_flag_is_found(CulArgFlag flag) {
	return flag & CUL_ARG_FOUND;
}

