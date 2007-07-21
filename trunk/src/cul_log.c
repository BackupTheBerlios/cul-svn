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
	size_t length = 0;
	va_list arg;

	/* write time if needed */
	if( type == CUL_LOG_CLOCK ) {
		snprintf(message, 13, "%10.5lf: ", (double)clock()/(double)CLOCKS_PER_SEC);
		length = strlen(message);
	}

	/* write message */
	va_start(arg, format);
	vsnprintf(message + length, CUL_LOG_MSG_SIZE - length - 1, format, arg);
	va_end(arg);

	/* handle message */
	switch( type ) {
		case CUL_LOG_CLOCK:
		case CUL_LOG_MESSAGE:
			if( cul_log_handler_get() != NULL )
				cul_log_handler_get()(module, type, message);
			else
				fprintf(cul_stream_get(), "%s", message);
			break;
		case CUL_LOG_WARNING:
		case CUL_LOG_ERROR:
		case CUL_LOG_FATAL:
			if( cul_log_handler_get() != NULL )
				cul_log_handler_get()(module, type, message);
			else {
				if( module != NULL ) fprintf(cul_stream_get(), "%s: %s", module, message);
				else                 fprintf(cul_stream_get(), "%s", message);
			}
	}

	/* handle abort */
	switch( type ) {
		case CUL_LOG_CLOCK:
		case CUL_LOG_MESSAGE:
		case CUL_LOG_WARNING: break;
		case CUL_LOG_ERROR:   if( cul_error_fatal_get() ) abort(); break;
		case CUL_LOG_FATAL:   abort(); break;
	}
}
