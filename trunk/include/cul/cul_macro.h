#ifndef __CUL_MACRO_H__
#define __CUL_MACRO_H__

/* include all needed function definitions */
#include <cul/cul_core.h>
#include <cul/cul_error.h>
#include <cul/cul_log.h>

#ifndef CUL_MODULE
#  define CUL_MODULE         ((char *) 0)
#endif

/* besic define for blocks */
#define CUL_STMT_START       do
#define CUL_STMT_END         while(0)

/* global macros */
#define CUL_SWAP(a, b, hold) ((void)((hold = a), (a = b), (b = hold)))
#define CUL_UNUSED(value)    CUL_STMT_START { (void)(value); } CUL_STMT_END

/* strigify macros */
#define CUL_STRINGIFY(str)   CUL_STRINGIFYx(str)
#define CUL_STRINGIFYx(str)  #str

#define CUL_FATAL(...) CUL_STMT_START {                                        \
		cul_log(CUL_MODULE, CUL_LOG_FATAL, __VA_ARGS__);                           \
	} CUL_STMT_END
#define CUL_FATAL_ERRNO(errno) CUL_STMT_START {                                \
		cul_log(CUL_MODULE, CUL_LOG_FATAL, "%s\n",                                 \
				cul_error_string(errno));                                              \
	} CUL_STMT_END

#define CUL_ERROR_ERRNO(errno) CUL_STMT_START {                                \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s\n",                                 \
				cul_error_string(errno));                                              \
	} CUL_STMT_END
#define CUL_ERROR_ERRNO_RET(value, errno) CUL_STMT_START {                     \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s\n",                                 \
				cul_error_string(errno));                                              \
		return (value);                                                            \
	} CUL_STMT_END
#define CUL_ERROR_ERRNO_RET_VOID(errno) CUL_STMT_START {                       \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s\n",                                 \
				cul_error_string(errno));                                              \
		return;                                                                    \
	} CUL_STMT_END

#define CUL_ERROR(...) CUL_STMT_START {                                        \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, __VA_ARGS__);                           \
	} CUL_STMT_END
#define CUL_ERROR_RET(value, ...) CUL_STMT_START {                             \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, __VA_ARGS__);                           \
		return (value);                                                            \
	} CUL_STMT_END
#define CUL_ERROR_RET_VOID(...) CUL_STMT_START {                               \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, __VA_ARGS__);                           \
		return;                                                                    \
	} CUL_STMT_END

#define CUL_CLOCK(...) CUL_STMT_START {                                        \
		cul_log(CUL_MODULE, CUL_LOG_CLOCK, __VA_ARGS__);                           \
	} CUL_STMT_END
#define CUL_MESSAGE(...) CUL_STMT_START {                                      \
		cul_log(CUL_MODULE, CUL_LOG_MESSAGE, __VA_ARGS__);                         \
	} CUL_STMT_END

#define CUL_CHECK(expr) CUL_STMT_START {                                       \
		if( !(expr) ) {                                                            \
			cul_log(CUL_MODULE, CUL_LOG_CHECK, "check '%s' failed\n", #expr);        \
		}                                                                          \
	} CUL_STMT_END
#define CUL_CHECK_RET(value, expr) CUL_STMT_START {                            \
		if( !(expr) ) {                                                            \
			cul_log(CUL_MODULE, CUL_LOG_CHECK, "check '%s' failed\n", #expr);        \
			return (value);                                                          \
		}                                                                          \
	} CUL_STMT_END
#define CUL_CHECK_RET_VOID(expr) CUL_STMT_START {                              \
		if( !(expr) ) {                                                            \
			cul_log(CUL_MODULE, CUL_LOG_CHECK, "check '%s' failed\n", #expr);        \
			return;                                                                  \
		}                                                                          \
	} CUL_STMT_END

#define CUL_ASSERT(expr) CUL_STMT_START {                                      \
		if( !(expr) ) CUL_FATAL("assertion '%s' failed\n", #expr);                 \
	} CUL_STMT_END

#endif /* __CUL_MACRO_H__ */
