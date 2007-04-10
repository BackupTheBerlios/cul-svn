#if !defined(CUL_ARG_H)
#define CUL_ARG_H

#include <cul/cul_global.h>

typedef enum _CulArgFlag CulArgFlag;
enum _CulArgFlag {
	/* type */
	CUL_ARG_BOOL    = 1,  /* option is a switch, no additional parameter */
	CUL_ARG_INT     = 2,  /* option has an integer number parameter (int) */
	CUL_ARG_DOUBLE  = 3,  /* option has an floating point number parameter (double) */
	CUL_ARG_STR     = 4,  /* option has an string parameter */
	CUL_ARG_STRV    = 5,  /* option has a string array parameter, store all flag parameters */

	/* flags */
	CUL_ARG_END        = 1 << 4,  /* indicate last option in argument table */
	CUL_ARG_JOIN       = 1 << 5,  /* indicate join of two tables */
	CUL_ARG_FOUND      = 1 << 6,  /* option was found in application aguments */
	CUL_ARG_HELP       = 1 << 7,  /* indicate no option, entry contains only help message to print on screen */
	CUL_ARG_REQUIRED   = 1 << 8,  /* option is required */

	/* masks */
	CUL_ARG_TYPE_MASK  = 0x000f,       /* mask for argument type */
	CUL_ARG_CONF_MASK  = 0xfff,        /* mask for argument configuration, flags and type */
	CUL_ARG_POS_MASK   = 0xffff << 12, /* mask for argument position */
	CUL_ARG_MASK       = 0xfffffff     /* maximal possible value for flag */
};

typedef struct _CulArg CulArg;
struct _CulArg {
	CulArgFlag flags;          /* option flags */
	const char short_name;     /* short name for option */
	const char *long_name;     /* long name for option */
	const char *desciption;    /* description of option */
	cul_ptr value;             /* callback for value, if option is not found it is left unchanged */
};

cul_errno cul_arg_parse(int *argc, char ***argv, CulArg **table);
void cul_arg_print_help(CulArg *table);
void cul_arg_free(CulArg *table);

/* utility functions */
CulArg *cul_arg_check_required(CulArg *table);
CulArg *cul_arg_search_short(CulArg *t, char arg);
CulArg *cul_arg_search_long(CulArg *t, const char *arg);

#endif
