#include <cul/cul_config.h>
#if defined(HAVE_ASPRINTF)
	#define _GNU_SOURCE
	#include <stdio.h>
#endif

#include <cul/cul_iof.h>
#include <cul/cul_io.h>

int cul_printf(const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vprintf(format, arg);
	va_end(arg);

	return done;
}

int cul_printf_stream(const char *format, ...) {
	va_list arg;
	int done;

	if( cul_stream_get() ) {
		va_start(arg, format);
		done = cul_vfprintf(cul_stream_get(), format, arg);
		va_end(arg);
	}

	return done;
}

int cul_fprintf(FILE *stream, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vfprintf(stream, format, arg);
	va_end(arg);

	return done;
}

int cul_fscanf(FILE *stream, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vfscanf(stream, format, arg);
	va_end(arg);

	return done;
}


int cul_sprintf(char *str, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vsprintf(str, format, arg);
	va_end(arg);

	return done;
}

int cul_snprintf(char *str, size_t size, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vsnprintf(str, size, format, arg);
	va_end(arg);

	return done;
}

int cul_asprintf(char **str, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = cul_vasprintf(str, format, arg);
	va_end(arg);

	return done;
}

int cul_vprintf_stream(const char *format, va_list ap) {
	return vfprintf(cul_stream_get(), format, ap);
}

int cul_vasprintf(char **str, const char *format, va_list ap) {
	int length;
#if defined(HAVE_ASPRINTF)
	length = vasprintf(str, format, ap);
	if( length < 0 )
		*str = NULL;
#else
	char character;
	*str = cul_malloc( (cul_vsnprintf(&character, 1, format, ap)+1)*sizeof(char) );
	length = vsprintf(*str, format, ap);
#endif
	return length;
}
