#include <cul/cul_global.h>
#include <cul/cul_iof.h>
#include <cul/cul_str.h>
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

const char *cul_log_filename_get(const char *file) __attribute__((nonnull));

void cul_log(const char *module, CulLogType type, const char *format, ...) {
	char message[CUL_LOG_MSG_SIZE] = "";
	size_t length;
	va_list arg;

	/* prepare prefixes */
	if( type == CUL_LOG_CLOCK )
		cul_snprintf(message, 15, "%10.5lf: ", (double)clock()/(double)CLOCKS_PER_SEC);

	if( module != NULL ) {
		cul_strcat(message, module);
		cul_strcat(message, ": ");
	}

	length = cul_strlen(message);

	va_start(arg, format);
	cul_vsnprintf(message + length, CUL_LOG_MSG_SIZE - length, format, arg);
	va_end(arg);

	if( cul_log_handler_get() == NULL )
		cul_printf_stream("%s", message);
	else
		cul_log_handler_get()(module, type, message);

	if( type == CUL_LOG_FATAL || (type == CUL_LOG_ERROR && cul_error_fatal_get()) )
		abort();
}

const char *cul_log_filename_get(const char *file) {
	const char *last, *cur;
	for( cur = file, last = file; *cur != '\0'; ++cur)
		if( *cur == '/' )
			last = cur;
	for( cur = last - 1; cur > file; --cur )
		if( *cur == '/' )
			break;
	return ++cur;
}
