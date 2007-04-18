#include <cul/cul_global.h>
#include <cul/cul_stream.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define CUL_LOG_MSG_SIZE 1024

cul_log_t *cul_log_handler = NULL;

cul_log_t *cul_log_handler_set(cul_log_t *handler) {
	cul_log_t *old_handler = cul_log_handler;
	cul_log_handler = handler;
	return old_handler;
}

cul_log_t *cul_log_handler_get(void) {
	return cul_log_handler;
}

void cul_log(const char *module, CulLogType type, const char *format, ...) {
	char message[CUL_LOG_MSG_SIZE] = "";
	size_t length;
	va_list arg;

	/* prepare prefixes */
	if( type == CUL_LOG_CLOCK )
		snprintf(message, 15, "%10.5lf: ", (double)clock()/(double)CLOCKS_PER_SEC);

	if( module != NULL ) {
		strcat(message, module);
		strcat(message, ": ");
	}

	length = strlen(message);

	va_start(arg, format);
	vsnprintf(message + length, CUL_LOG_MSG_SIZE - length, format, arg);
	va_end(arg);

	if( cul_log_handler_get() == NULL )
		fprintf(cul_stream_get(), "%s", message);
	else
		cul_log_handler_get()(module, type, message);

	if( type == CUL_LOG_FATAL || (type == CUL_LOG_ERROR && cul_error_fatal_get()) )
		abort();
}
