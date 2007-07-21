#ifndef CUL_ARG_H
#define CUL_ARG_H

#include <cul/cul_global.h>

typedef struct _CulArg     CulArg;
typedef enum   _CulArgFlag CulArgFlag;

/** \brief Argument flag describing its type and properties.
 * 
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
	CUL_ARG_BOOL       = 1,  /**< option is a switch, no additional parameter */
	CUL_ARG_INT        = 2,  /**< option has an integer number parameter (int) */
	CUL_ARG_DOUBLE     = 3,  /**< option has an floating point number parameter (double) */
	CUL_ARG_STR        = 4,  /**< option has an string parameter */
	CUL_ARG_STRV       = 5,  /**< option has a string array parameter, store all flag parameters */

	/* type flags */
	CUL_ARG_NEED       = 1 << 4,  /**< option is required */
	CUL_ARG_FOUND      = 1 << 5,  /**< option was found in application aguments */

	/* non-type */
	CUL_ARG_END        = 1 << 6,  /**< indicate last option in argument table */
	CUL_ARG_HELP       = 1 << 7,  /**< indicate no option, entry contains only help message to print on screen */

	/* internal masks */
	CUL_ARG_TYPE_MASK  = 0x00f,        /**< mask for type */
	CUL_ARG_NTYPE_MASK = 0x0c0,        /**< mask for non-type */
	CUL_ARG_CONF_MASK  = 0xfff,        /**< mask for argument configuration, flags and type */
	CUL_ARG_POS_MASK   = 0xffff << 12, /**< mask for argument position */
	CUL_ARG_MASK       = 0xfffffff     /**< maximal possible flag value */
};

#define CUL_ARG_NULL {CUL_ARG_END, 0, NULL, NULL, NULL}

/** \brief Argument description structure.
 * 
 * Structure describes single command line argument or additional 
 * help/description that should be printed as a help information.
 */
struct _CulArg {
	CulArgFlag flags;          /**< option flags */
	const char short_name;     /**< short name for option */
	const char *long_name;     /**< long name for option */
	const char *description;   /**< description of option */
	cul_ptr value;             /**< callback for value, if option is not found it is left unchanged */
};

cul_errno cul_arg_parse         (int *argc, char ***argv, CulArg **table);
void      cul_arg_print_help    (CulArg *t);
void      cul_arg_free          (CulArg *t, cul_bool is_free_value);

/* utility functions */
void      cul_arg_connect       (CulArg *t, CulArg *connect);
void      cul_arg_disconnect    (CulArg *t, CulArg *connect);
CulArg   *cul_arg_check_required(CulArg *t);
CulArg   *cul_arg_search_short  (CulArg *t, char arg);
CulArg   *cul_arg_search_long   (CulArg *t, const char *arg);

#endif /* CUL_ARG_H */
