#ifndef __CUL_LOG_H__
#define __CUL_LOG_H__

#include <cul/cul_core.h>

typedef enum _CulLogType CulLogType;
typedef void cul_log_f(const char *module, CulLogType type, const char *msg);

enum _CulLogType {
	CUL_LOG_FATAL,
	CUL_LOG_ERROR,
	CUL_LOG_CHECK,
	CUL_LOG_MESSAGE,
	CUL_LOG_CLOCK,
};

cul_log_f *cul_log_handler_set(cul_log_f *handler);
cul_log_f *cul_log_handler_get();
void       cul_log            (const char *module, CulLogType type, const char *format, ...);

#endif /* __CUL_LOG_H__ */
