#if !defined(CUL_STREAM_H)
#define CUL_STREAM_H

#include <stdarg.h>
#include <stdio.h>
#include <cul/cul_global.h>

int cul_printf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
int cul_fprintf(FILE *stream, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
int cul_fscanf(FILE *stream, const char *format, ...) __attribute__ ((format (scanf, 2, 3)));

static inline int cul_vprintf(const char *format, va_list ap);
static inline int cul_vfprintf(FILE *stream, const char *format, va_list ap);
static inline int cul_vfscanf(FILE *stream, const char *format, va_list ap);

int cul_printf_stream(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
int cul_vprintf_stream(const char *format, va_list ap);

FILE *cul_stream_get(void);
FILE *cul_stream_set(FILE *stream);
FILE *cul_stream_default(void);

/* implementations */

static inline int cul_vprintf(const char *format, va_list ap) {
	return vprintf(format, ap);
};

static inline int cul_vfprintf(FILE *stream, const char *format, va_list ap) {
	return vfprintf(stream, format, ap);
}

static inline int cul_vfscanf(FILE *stream, const char *format, va_list ap) {
	return vfscanf(stream, format, ap);
}

#endif
