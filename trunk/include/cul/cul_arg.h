#ifndef __CUL_ARG_H__
#define __CUL_ARG_H__

#include <cul/cul_global.h>

typedef struct _CulArg     CulArg;
typedef enum   _CulArgFlag CulArgFlag;

/**
 * Argument flag describe how to interpret specific argument, if it take 
 * additional option or is only switch. Argument could be marked as required.
 * It is also possible to use specific argument entry only as additional 
 * description.
 * 
 * NOTE: After argument parsing flag holds additional information, like if 
 * argument was found on command line or its position.  
 */
enum _CulArgFlag {
	/* type */
	CUL_ARG_TRUE       = 1,  /* option is a switch, value is set to true (cul_bool) */
	CUL_ARG_FALSE      = 2,  /* option is a switch, value is set to false (cul_bool) */
	CUL_ARG_COUNT      = 3,  /* option is a switch, value is increased by number of occurences (int) */
	CUL_ARG_INT        = 4,  /* option has an integer number parameter (int) */
	CUL_ARG_DOUBLE     = 5,  /* option has an floating point number parameter (double) */
	CUL_ARG_STR        = 6,  /* option has an string parameter */

	/* type flags */
	CUL_ARG_NEED       = 1 << 4,  /* option is required */
	CUL_ARG_FOUND      = 1 << 5,  /* option was found in application aguments */

	/* non-type */
	CUL_ARG_END        = 1 << 6,  /* indicate last option in argument table */
	CUL_ARG_PRINT      = 1 << 7,  /* indicate no option, entry contains only help message to print on screen */

	/* internal masks */
	CUL_ARG_TYPE_MASK  = 0x00f,        /* mask for type */
	CUL_ARG_NTYPE_MASK = 0x0c0,        /* mask for non-type */
	CUL_ARG_CONF_MASK  = 0xfff,        /* mask for argument configuration, flags and type */
	CUL_ARG_POS_MASK   = 0xffff << 12, /* mask for argument position */
	CUL_ARG_MASK       = 0xfffffff     /* maximal possible flag value */
};

/* utility macros */
#define CUL_ARG_HELP(message) {CUL_ARG_PRINT, 0, NULL, message, NULL}
#define CUL_ARG_NULL          {CUL_ARG_END,   0, NULL, NULL,    NULL}

/** Command line argument entry
 * Structure describes single accepted command line argument or additional 
 * help/description that should be printed as a help information.
 */
struct _CulArg {
	CulArgFlag flags;          /* option flags */
	const char short_name;     /* short name for option */
	const char *long_name;     /* long name for option */
	const char *description;   /* description of option */
	cul_ptr value;             /* callback for value, if option is not found it is left unchanged */
};

cul_errno cul_arg_parse         (int *argc, char ***argv, CulArg **table);      /* parse command line arguments according to CulArg table */
void      cul_arg_print         (CulArg *this);                                 /* print CulArg table help information */
void      cul_arg_free          (CulArg *this, cul_bool free_values);           /* free data associated with CulArg table, including values */

/* utility functions */
void      cul_arg_connect       (CulArg *this, CulArg *other);                  /* connect together two CulArg tables */
CulArg   *cul_arg_find_short    (const CulArg *this, char arg);                 /* find short argument entry in CulArg table */
CulArg   *cul_arg_find_long     (const CulArg *this, const char *arg);          /* find long argument entry in CulArg table */
cul_bool  cul_arg_after         (const CulArg *this, const CulArg *other);      /* check relative position of two different entries on command line */
cul_bool  cul_arg_before        (const CulArg *this, const CulArg *other);      /* check relative position of two different entries on command line */

#endif /* __CUL_ARG_H__ */
