#ifndef CUL_MACRO_H
#define CUL_MACRO_H

/* include all needed function definitions */
#include <cul/cul_global.h>

#ifndef CUL_MODULE
	#define CUL_MODULE ((char *) 0)
#endif

#define CUL_UNUSED(val)      { ((void)val); }
#define CUL_SWAP(a, b, hold) ((void)((hold = a), (a = b), (b = hold)))
#define CUL_POW_2(a)         ((a)*(a))

#define CUL_STMT_START do
#define CUL_STMT_END   while(0)

#define CUL_FATAL_ERRNO(errno) CUL_STMT_START {              \
		cul_log(CUL_MODULE, CUL_LOG_FATAL, "%s: (%s:%d) %s\n",   \
			__PRETTY_FUNCTION__,                                   \
			__FILE__,                                              \
			__LINE__,                                              \
			cul_error_string(errno));                              \
	} CUL_STMT_END
#define CUL_FATAL(...) CUL_STMT_START {                      \
		cul_log(CUL_MODULE, CUL_LOG_FATAL, __VA_ARGS__);         \
	} CUL_STMT_END

#define CUL_ERROR_ERRNO_RET_VAL(val, errno) CUL_STMT_START { \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s: (%s:%d) %s\n",   \
			__PRETTY_FUNCTION__,                                   \
			__FILE__,                                              \
			__LINE__,                                              \
			cul_error_string(errno));                              \
		return (val);                                            \
	} CUL_STMT_END
#define CUL_ERROR_ERRNO_RET(errno, ...) CUL_STMT_START {     \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s: (%s:%d) %s\n",   \
			__PRETTY_FUNCTION__,                                   \
			__FILE__,                                              \
			__LINE__,                                              \
			cul_error_string(errno));                              \
		return __VA_ARGS__;                                      \
	} CUL_STMT_END
#define CUL_ERROR_ERRNO(errno) CUL_STMT_START {              \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, "%s: (%s:%d) %s\n",   \
			__PRETTY_FUNCTION__,                                   \
			__FILE__,                                              \
			__LINE__,                                              \
			cul_error_string(errno));                              \
	} CUL_STMT_END
#define CUL_ERROR(...) CUL_STMT_START {                      \
		cul_log(CUL_MODULE, CUL_LOG_ERROR, __VA_ARGS__);         \
	} CUL_STMT_END

#define CUL_CLOCK(...) CUL_STMT_START {                      \
		cul_log(CUL_MODULE, CUL_LOG_CLOCK, __VA_ARGS__);         \
	} CUL_STMT_END
#define CUL_MESSAGE(...) CUL_STMT_START {                    \
		cul_log(CUL_MODULE, CUL_LOG_MESSAGE, __VA_ARGS__);       \
	} CUL_STMT_END
#define CUL_WARNING(...) CUL_STMT_START {                    \
		cul_log(CUL_MODULE, CUL_LOG_WARNING, __VA_ARGS__);       \
	} CUL_STMT_END

#define CUL_ASSERT(expr) CUL_STMT_START {                    \
		if( (expr) ) {                                           \
		}                                                        \
		else {                                                   \
			CUL_FATAL("%s: (%s:%d) assertion '%s' failed\n",       \
				__PRETTY_FUNCTION__,                                 \
				__FILE__,                                            \
				__LINE__,                                            \
				#expr);                                              \
		}                                                        \
	} CUL_STMT_END
#define CUL_CHECK(expr) CUL_STMT_START {                     \
		if( (expr) ) {                                           \
		}                                                        \
		else {                                                   \
			CUL_WARNING("%s: (%s:%d) check '%s' failed\n",         \
				__PRETTY_FUNCTION__,                                 \
				__FILE__,                                            \
				__LINE__,                                            \
				#expr);                                              \
		}                                                        \
	} CUL_STMT_END
#define CUL_CHECK_RET(expr, ...) CUL_STMT_START {            \
		if( (expr) ) {                                           \
		}                                                        \
		else {                                                   \
			CUL_WARNING("%s: (%s:%d) check '%s' failed\n",         \
				__PRETTY_FUNCTION__,                                 \
				__FILE__,                                            \
				__LINE__,                                            \
				#expr);                                              \
			return __VA_ARGS__;                                    \
		}                                                        \
	} CUL_STMT_END

#endif /* CUL_MACRO_H */
