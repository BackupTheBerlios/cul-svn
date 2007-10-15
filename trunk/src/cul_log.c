#include <cul/cul_global.h>
#include <cul/cul_stream.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define CUL_LOG_MSG_SIZE 1024

cul_log_f *cul_log_handler = NULL;

cul_log_f *cul_log_handler_set(cul_log_f *handler) {
	cul_log_f *old_handler = cul_log_handler;
	cul_log_handler = handler;
	return old_handler;
}

cul_log_f *cul_log_handler_get(void) {
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
	case CUL_LOG_FATAL:
	case CUL_LOG_ERROR:
		if( cul_log_handler_get() == NULL ) {
			if( module != NULL ) fprintf(cul_stream_get(), "%s: %s", module, message);
			else                 fprintf(cul_stream_get(), "%s", message);
		} else
			cul_log_handler_get()(module, type, message);
		break;
	case CUL_LOG_CHECK:
	case CUL_LOG_MESSAGE:
	case CUL_LOG_CLOCK:
		if( cul_log_handler_get() == NULL )
			fprintf(cul_stream_get(), "%s", message);
		else
			cul_log_handler_get()(module, type, message);
		break;
	}

	/* handle abort */
	switch( type ) {
	case CUL_LOG_FATAL:   abort(); break;
	case CUL_LOG_ERROR:   if( cul_error_fatal_get() ) abort(); break;
	case CUL_LOG_CHECK:
	case CUL_LOG_MESSAGE:
	case CUL_LOG_CLOCK:   break;
	}
}
