#ifndef __CUL_ARG_H__
#define __CUL_ARG_H__

#include <cul/cul_global.h>

/* argument table entry */
typedef struct _CulArg     CulArg;
/* aegument entry flags */
typedef enum   _CulArgFlag CulArgFlag;

/* basic defines for CulArgFlag */
#define CUL_ARG_POS_SHIFT 12
#define CUL_ARG_EX_SHIFT  28

/** Command line argument flag.
 * Argument flag describe how to interpret specific argument, if it take
 * additional option or is only switch. Argument could be marked as required
 * or exclusive in group. It is also possible to use specific argument entry
 * only as additional description.
 *
 * NOTE: After argument parsing flag holds additional information, i.e. if
 * argument was found on command line or its position.
 */
enum _CulArgFlag {
	/* input type entry */
	CUL_ARG_TRUE       = 1,  /* option is a switch, value is set to true (cul_bool) */
	CUL_ARG_FALSE      = 2,  /* option is a switch, value is set to false (cul_bool) */
	CUL_ARG_COUNT      = 3,  /* option is a switch, value is increased by number of occurrences (int) */
	CUL_ARG_INT        = 4,  /* option has integer number parameter (int) */
	CUL_ARG_DOUBLE     = 5,  /* option has floating point number parameter (double) */
	CUL_ARG_STR        = 6,  /* option has string parameter */
	CUL_ARG_STRV       = 7,  /* option has string parameter, multiple occurrences are added */

	/* other entry types */
	CUL_ARG_END        = 1 << 4,   /* indicate last option in argument table */
	CUL_ARG_PRINT      = 1 << 5,   /* indicate entry with help message */

	/* input entry modifier flags */
	CUL_ARG_EX         = 1 << 11,  /* option is exclusive */
	CUL_ARG_NEED       = 1 << 10,  /* option is required */
	CUL_ARG_FOUND      = 1 << 9,   /* option was found in application arguments */

	/* CUL_ARG_END entry modifier flags */
	/* CUL_ARG_PRINT entry modifier flags */

	/* internal masks for processing */
	CUL_ARG_INPUT_MASK = 0x00f,                       /* mask for input type */
	CUL_ARG_OTHER_MASK = 0x030,                       /* mask for other types */
	CUL_ARG_TYPE_MASK  = 0x03f,                       /* mask for type */
	CUL_ARG_POS_MASK   = 0xffff << CUL_ARG_POS_SHIFT, /* mask for position */
	CUL_ARG_EX_MASK    = 0x7    << CUL_ARG_EX_SHIFT,  /* mask for exclusive group */
	CUL_ARG_MASK       = 0x7fffffff                   /* mask for whole flag value */
};

/* argument utility macros */
#define CUL_ARG_HELP(message)      {CUL_ARG_PRINT,                 0, NULL, message, NULL}
#define CUL_ARG_NULL(modifiers)    {CUL_ARG_END | (modifiers),     0, NULL, NULL,    NULL}
#define CUL_ARG_NULL_DEFAULT       CUL_ARG_NULL(0)

/* type helpers macros */
/* need macros */
#define CUL_ARG_TRUE_NEED          (CUL_ARG_TRUE   | CUL_ARG_NEED)
#define CUL_ARG_FALSE_NEED         (CUL_ARG_FALSE  | CUL_ARG_NEED)
#define CUL_ARG_COUNT_NEED         (CUL_ARG_COUNT  | CUL_ARG_NEED)
#define CUL_ARG_INT_NEED           (CUL_ARG_INT    | CUL_ARG_NEED)
#define CUL_ARG_DOUBLE_NEED        (CUL_ARG_DOUBLE | CUL_ARG_NEED)
#define CUL_ARG_STR_NEED           (CUL_ARG_STR    | CUL_ARG_NEED)
#define CUL_ARG_STRV_NEED          (CUL_ARG_STRV   | CUL_ARG_NEED)
/* ex macros */
#define CUL_ARG_TRUE_EX(id)        (CUL_ARG_TRUE   | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_FALSE_EX(id)       (CUL_ARG_FALSE  | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_COUNT_EX(id)       (CUL_ARG_COUNT  | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_INT_EX(id)         (CUL_ARG_INT    | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_DOUBLE_EX(id)      (CUL_ARG_DOUBLE | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_STR_EX(id)         (CUL_ARG_STR    | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
/* ex/need macros */
#define CUL_ARG_TRUE_NEED_EX(id)   (CUL_ARG_TRUE   | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_FALSE_NEED_EX(id)  (CUL_ARG_FALSE  | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_COUNT_NEED_EX(id)  (CUL_ARG_COUNT  | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_INT_NEED_EX(id)    (CUL_ARG_INT    | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_DOUBLE_NEED_EX(id) (CUL_ARG_DOUBLE | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))
#define CUL_ARG_STR_NEED_EX(id)    (CUL_ARG_STR    | CUL_ARG_NEED | CUL_ARG_EX | ((id) << CUL_ARG_EX_SHIFT))

/* utility macros */
#define CUL_ARG_FLAG_POS(flag)     (((flag) & CUL_ARG_POS_MASK) >> CUL_ARG_POS_SHIFT)
#define CUL_ARG_FLAG_EX(flag)      (((flag) & CUL_ARG_EX_MASK) >> CUL_ARG_EX_SHIFT)

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

cul_errno cul_arg_parse        (int *argc, char ***argv, CulArg **table);               /* parse command line arguments according to CulArg table */
cul_errno cul_arg_parse_auto   (int *argc, char ***argv, CulArg **table);               /* parse command line arguments according to CulArg table and automatically free data at destructor */
cul_bool  cul_arg_error        (int argc, char **argv, CulArg *entry, cul_errno error); /* print error message (if any) returned from parse functions */
void      cul_arg_print_default(const CulArg *table);                                   /* print CulArg table help information */
void      cul_arg_free         (CulArg *table);                                         /* free internal associated with CulArg table, including values */

void      cul_arg_connect      (CulArg *table, CulArg *other);                          /* connect together two CulArg tables */
CulArg   *cul_arg_find         (const CulArg *table, cul_ptr value);                    /* find value argument entry in CulArg table */
cul_bool  cul_arg_found        (const CulArg *table, cul_ptr value);                    /* check if value was found in CulArg table */
cul_bool  cul_arg_after        (const CulArg *table, const CulArg *other);              /* check relative position of two different entries on command line */
cul_bool  cul_arg_before       (const CulArg *table, const CulArg *other);              /* check relative position of two different entries on command line */

#endif /* __CUL_ARG_H__ */

