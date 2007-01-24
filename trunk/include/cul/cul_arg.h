#if !defined(CUL_ARG_H)
#define CUL_ARG_H

#include <cul/cul_global.h>

typedef enum _CulArgFlag CulArgFlag;
enum _CulArgFlag {
	CUL_ARG_BOOL         = 1,       /* option is a swith, no additional parameter */
	CUL_ARG_INT          = 2,       /* option has an integer parameter (int) */
	CUL_ARG_DOUBLE       = 3,       /* option has an float parameter (double) */
	CUL_ARG_STRING       = 4,       /* option has an string parameter */
	CUL_ARG_CALLBACK     = 14,      /* option passed to callback as a string */
	CUL_ARG_MASK         = 15,      /* mask for internal use */
	CUL_ARG_END          = 1 << 4,  /* flag for last entry in option list */
	CUL_ARG_HELP         = 1 << 5,  /* entry contains general description, to use with help generation */
	CUL_ARG_GROUP        = 1 << 6,  /* section indicate separate group */
	CUL_ARG_REQUIRED     = 1 << 7,  /* option is required */
	CUL_ARG_FOUND        = 1 << 8   /* option was found in application aguments */
};

typedef struct _CulArg CulArg;
typedef cul_bool cul_arg_callback_f(const char *arg, CulArg *t);

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
