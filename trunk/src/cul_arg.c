#include <cul/cul_arg.h>
#include <cul/cul_stream.h>
#include <cul/cul_base.h>
#include <cul/cul_str.h>

#include <stdlib.h>
#include <string.h>

/* private functions */
static inline void _cul_arg_cmd_next       (int *argc, char ***argv);
static cul_errno   _cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table, size_t n);
static cul_errno   _cul_arg_cmd_parse_long (int *argc, char ***argv, CulArg *table, size_t n);
static cul_bool    _cul_arg_cmd_convert    (const char *arg, CulArg *entry, size_t n);
static CulArg     *_cul_arg_end            (const CulArg *this);
static CulArg     *_cul_arg_end_last       (const CulArg *this);

/* Parse program arguments using argument tables */
cul_errno cul_arg_parse(int *argc, char ***argv, CulArg **table) {
	size_t pos = 0;

	/* omit first parameter */
	_cul_arg_cmd_next(argc, argv);

	while( *argc > 0 ) {
		char *arg = **argv;
		cul_errno result;

		if( *arg == '-' ) {
			if( *(++arg) == '-' ) {
				if( *(++arg) == CUL_STR_NULL )
					/* finish parsing */
					break;

				/* long option */
				result = _cul_arg_cmd_parse_long(argc, argv, *table, pos);
				if( result != CUL_SUCCESS )
					return result;
				else
					pos += 1;

				/* parse next options */
				continue;
			}
			if( *arg == CUL_STR_NULL )
				return CUL_EARGUNK;

			/* short option */
			result = _cul_arg_cmd_parse_short(argc, argv, *table, pos);
			if( result != CUL_SUCCESS )
				return result;
			else
				pos += 1;

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

void cul_arg_connect(CulArg *this, CulArg *other) {
	/* connect tables */
	_cul_arg_end_last(this)->value = other;
}

void cul_arg_connect_next(CulArg *this, CulArg *other) {
	/* find end of table */
	this = _cul_arg_end(this);

	/* check if we have to modify other table */
	if( this->value != NULL )
		_cul_arg_end_last(other)->value = this->value;

	/* connect tables */
	this->value = other;
}

void cul_arg_disconnect(CulArg *this, CulArg *other) {
	/* find other table */
	while( CUL_TRUE ) {
		this = _cul_arg_end(this);

		if( this->value == NULL)
			return;

		if( this->value == other ) {
			other = _cul_arg_end(other);
			this->value = other->value;
			other->value = NULL;
		}
	}
	
}

void cul_arg_print(CulArg *this) {
	while( this != NULL ) {
		switch( this->flags & CUL_ARG_NTYPE_MASK ) {
		case CUL_ARG_END:
			this = this->value;
			break;
		case CUL_ARG_PRINT:
			fprintf(cul_stream_get(), "%s\n", this->description);
			this += 1;
			break;
		default:
			if( this->short_name ) {
				if( this->long_name )
					fprintf(cul_stream_get(),"  -%c, --%-16s  %s\n",
							this->short_name, this->long_name, this->description);
				else
					fprintf(cul_stream_get(),"  -%-21c  %s\n",
							this->short_name, this->description);
			}
			else if( this->long_name )
				fprintf(cul_stream_get(), "  --%-20s  %s\n",
						this->long_name, this->description);
			this += 1;
			break;
		}
	}
}

void cul_arg_free(CulArg *this, cul_bool free_values) {
	while( this != NULL )
		switch( this->flags & CUL_ARG_NTYPE_MASK ) {
		case CUL_ARG_END:  this = this->value; break;
		case CUL_ARG_PRINT: this += 1; break;
		default:
			if( this->flags & CUL_ARG_FOUND ) {
				switch( this->flags & CUL_ARG_TYPE_MASK ) {
				case CUL_ARG_STR:
					if( free_values ) free(*(char **)this->value);
					break;
				case CUL_ARG_STRV:
					if( free_values ) cul_strv_free(*(char ***)this->value);
					break;
				default:
					break;
				}
			}
			this += 1;
			break;
	}
}

CulArg *cul_arg_check_required(const CulArg *this) {
	while( this != NULL ) {
		switch( this->flags & CUL_ARG_NTYPE_MASK ) {
		case CUL_ARG_END: this = this->value; break;
		case CUL_ARG_PRINT: this += 1; break;
		default:
			if( this->flags & CUL_ARG_NEED && !(this->flags & CUL_ARG_FOUND) )
				return (CulArg *)this;
			this += 1;
			break;
		}
	}
	return NULL;
}

CulArg *cul_arg_find_short(const CulArg *this, char arg) {
	while( this != NULL ) {
		switch( this->flags & CUL_ARG_NTYPE_MASK ) {
		case CUL_ARG_END: this = this->value; break;
		case CUL_ARG_PRINT: this += 1; break;
		default:
			if( this->short_name == arg )
				return (CulArg *)this;
			this += 1;
			break;
		}
	}
	return NULL;
}

CulArg *cul_arg_find_long(const CulArg *this, const char *arg) {
	const char *pos;
	size_t length;

	if( (pos = strchr(arg,'=')) )
		length = pos - arg;
	else
		length = strlen(arg);

	while( this != NULL ) {
		switch( this->flags & CUL_ARG_NTYPE_MASK ) {
		case CUL_ARG_END: this = this->value; break;
		case CUL_ARG_PRINT: this += 1; break;
		default:
			if( this->long_name != NULL &&
					strncmp(arg, this->long_name, length) == 0 &&
					this->long_name[length] == CUL_STR_NULL )
				return (CulArg *)this;
			this += 1;
			break;
		}
	}
	return NULL;
}

static inline void _cul_arg_cmd_next(int *argc, char ***argv) {
	--(*argc);
	++(*argv);
}

static cul_errno _cul_arg_cmd_parse_short(int *argc, char ***argv, CulArg *table, size_t n) {
	const char *arg_string = **argv + 1;
	cul_bool is_multi_flag = CUL_FALSE;
	CulArg *entry;

	while( *arg_string ) {
		/* find entry in options table */
		if( !(entry = cul_arg_find_short(table, *arg_string)) )
			return CUL_EARGUNK;

		const CulArgFlag flag = (entry->flags & CUL_ARG_TYPE_MASK);
		const cul_bool is_option_bool = (flag == CUL_ARG_BOOL);

		/* we have more flags than one */
		if( is_multi_flag ) {
			if( !is_option_bool )
				return CUL_EARGCONV;

			/* convert flag option */
			if( !_cul_arg_cmd_convert(arg_string, entry, n) )
				return CUL_EARGCONV;

			/* end of multiple bool short flags */
			if( *(++arg_string) == CUL_STR_NULL ) {
				_cul_arg_cmd_next(argc, argv);
				return CUL_SUCCESS;
			}
		/* this is first flag */
		}	else {
			size_t size;

			/* if not bool we have to move to flag option */
			if( !is_option_bool ) {
				/* check if there is something after flag */
				if( *(arg_string+1) != CUL_STR_NULL ) {
					/* option is right after flag */
					++arg_string;
					size = 1;
				} else {
					/* option is a separate argument */

					/* check if we have more arguments present */
					if( *argc < 2 )
						return CUL_EARGCONV;

					arg_string = *(*argv + 1);
					size = 2;
				}
			} else {
				/* this is first of possible multiple bool options */

				/* check if we have more flags */
				if( *(++arg_string) != CUL_STR_NULL ) {
					is_multi_flag = CUL_TRUE;
					size = 0;
				} else
					size = 1;
			}

			/* convert flag option */
			if( !_cul_arg_cmd_convert(arg_string, entry, n) )
				return CUL_EARGCONV;

			if( size > 0 ) {
				/* move to next argument */
				while( size-- > 0 )
					_cul_arg_cmd_next(argc, argv);

				return CUL_SUCCESS;
			}
		}
	}
	return CUL_FAILURE;
}

static cul_errno _cul_arg_cmd_parse_long(int *argc, char ***argv, CulArg *table, size_t n) {
	const char *arg_string = **argv + 2;
	const char *arg_option = strchr(arg_string, '=');
	CulArg *entry;

	/* check if we have option */
	if( *arg_string ) {
		/* find entry in options table */
		if( !(entry = cul_arg_find_long(table, arg_string)) )
			return CUL_EARGUNK;

		size_t size;
		const CulArgFlag flag = (entry->flags & CUL_ARG_TYPE_MASK);
		const cul_bool is_option_bool = (flag == CUL_ARG_BOOL);

		/* if not bool we have to move to flag option */
		if( !is_option_bool ) {
			/* check if there is something after flag */
			if( arg_option ) {
				/* option is right after flag */
				arg_string = arg_option+1;
				size = 1;
			} else {
				/* option is a separate argument */

				/* check if we have more arguments present */
				if( *argc < 2 )
					return CUL_EARGCONV;

				arg_string = *(*argv + 1);
				size = 2;
			}
		} else {
			/* check if there is flag option present */
			if( arg_option )
				return CUL_EARGCONV;

			size = 1;
		}

		/* convert flag option */
		if( !_cul_arg_cmd_convert(arg_string, entry, n) )
			return CUL_EARGCONV;

		/* move to next argument */
		while( size-- > 0 )
			_cul_arg_cmd_next(argc, argv);

		return CUL_SUCCESS;
	}
	return CUL_FAILURE;
}

static cul_bool _cul_arg_cmd_convert(const char *arg, CulArg *entry, size_t n) {
	char* end;

	switch( entry->flags & CUL_ARG_TYPE_MASK ) {
	case CUL_ARG_BOOL:
		*((cul_bool *)entry->value) = CUL_TRUE;
		break;
	case CUL_ARG_INT:
		if( *arg ) {
			long tmp = strtol(arg, &end, 10);
			if( !*end && tmp == (int)tmp ) {
				*((int *)entry->value) = (int)tmp;
				break;
			}
		}
		return CUL_FALSE;
	case CUL_ARG_DOUBLE:
		if( *arg ) {
			double tmp = strtod(arg, &end);
			if( !*end ) {
				*((double *)entry->value) = tmp;
				break;
			}
		}
		return CUL_FALSE;
	case CUL_ARG_STR:
		if( *arg ) {
			char *tmp = cul_strdup(arg);
			if( tmp != NULL ) {
				/* free old string, only if already found */
				if( entry->flags & CUL_ARG_FOUND )
					free(*(char **)entry->value);
				*(char **)entry->value = tmp;
				break;
			}
		}
		return CUL_FALSE;
	case CUL_ARG_STRV:
		if( *arg ) {
			char **strv = *(char ***)entry->value;
			size_t size = strv == NULL? 0: cul_strv_size(strv);

			char **tmpv = malloc( (size+2)*sizeof(char *) );
			if( tmpv != NULL ) {
				char *tmp = cul_strdup(arg);
				if( tmp != NULL ) {

					/* copy old strv and free previous content if needed */
					if( strv != NULL ) {
						if( entry->flags & CUL_ARG_FOUND ) {
							memcpy(tmpv, strv, size*sizeof(char **));
							free(strv);
						}	else {
							/* we have to duplicate default values */
							/* consitency requirement for free routine */
							for( size_t i=0; i<size; ++i)
								if( (tmpv[i] = cul_strdup(strv[i])) == NULL ) {
									cul_strv_free(tmpv);
									free(tmp);
									return CUL_FALSE;
								}
						}
					}

					/* add one string */
					tmpv[size] = tmp;
					tmpv[size+1] = NULL;

					*(char ***)entry->value = tmpv;
					break;
				} else
					free(tmpv);
			}
		}
		return CUL_FALSE;
	default:
		return CUL_FALSE;
	}

	/* mark flag as found */
	entry->flags |= CUL_ARG_FOUND;

	/* clear and set position */
	entry->flags &= ~CUL_ARG_POS_MASK;
	entry->flags |= n << 12;

	return CUL_TRUE;
}

CulArg *_cul_arg_end(const CulArg *this) {
	/* find end of table */
	for(; !(this->flags & CUL_ARG_END); this += 1) ;
	return (CulArg *)this;
}

CulArg *_cul_arg_end_last(const CulArg *this) {
	/* find end of table */
	for(; !(this->flags & CUL_ARG_END); this += 1) ;
	/* find last end of table */
	while( this->value != NULL )
		for(this = this->value; !(this->flags & CUL_ARG_END); this += 1) ;
	return (CulArg *)this;
}

