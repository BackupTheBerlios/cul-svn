#if !defined(CUL_LOG_H)
#define CUL_LOG_H

#include <cul/cul_global_base.h>
#include <cul/cul_error.h>

typedef enum _CulLogType CulLogType;
typedef void cul_log_t(const char *module, CulLogType type, const char *msg);

enum _CulLogType {
	CUL_LOG_CLOCK,
	CUL_LOG_ERROR,
	CUL_LOG_FATAL,
	CUL_LOG_MESSAGE,
	CUL_LOG_WARNING
};

cul_log_t *cul_log_handler_set(cul_log_t *handler);
cul_log_t *cul_log_handler_get(void);

void cul_log(const char *module, CulLogType type, const char *format, ...) __attribute__ ((format (printf, 3, 4)));

#endif
