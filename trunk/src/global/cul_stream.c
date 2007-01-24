#include <cul/cul_stream.h>

FILE *cul_stream = NULL;

void init_cul_stream(void) __attribute__ ((constructor));
void init_cul_stream(void) {
	cul_stream = cul_stream_default();
}

int cul_printf(const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = vprintf(format, arg);
	va_end(arg);

	return done;
}

int cul_vprintf(const char *format, va_list ap) {
	return vprintf(format, ap);
}

int cul_fprintf(FILE *stream, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = vfprintf(stream, format, arg);
	va_end(arg);

	return done;
}

int cul_vfprintf(FILE *stream, const char *format, va_list ap) {
	return vfprintf(stream, format, ap);
}

int cul_fscanf(FILE *stream, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = vfscanf(stream, format, arg);
	va_end(arg);

	return done;
}

int cul_vfscanf(FILE *stream, const char *format, va_list ap) {
	return vfscanf(stream, format, ap);
}

int cul_stream_printf(const char *format, ...) {
	va_list arg;
	int done = 0;

	if( cul_stream_get() ) {
		va_start(arg, format);
		done = vfprintf(cul_stream_get(), format, arg);
		va_end(arg);
	}

	return done;
}

int cul_stream_vprintf(const char *format, va_list ap) {
	return vfprintf(cul_stream_get(), format, ap);
}

FILE *cul_stream_get(void) {
	return cul_stream;
}

FILE *cul_stream_set(FILE *stream) {
	FILE *old_stream = cul_stream;
	cul_stream = stream;
	return old_stream;
}

FILE *cul_stream_default(void) {
	return stderr;
}
