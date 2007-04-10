#ifndef CUL_IOF_H
#define CUL_IOF_H

#include <cul/cul_global.h>
#include <stdarg.h>
#include <stdio.h>

/* iof stream and string functions */

int cul_printf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
int cul_printf_stream(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
int cul_fprintf(FILE *stream, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
int cul_fscanf(FILE *stream, const char *format, ...) __attribute__ ((format (scanf, 2, 3)));

int cul_sprintf(char *str, const char *format, ...)  __attribute__ ((format (printf, 2, 3)));
int cul_snprintf(char *str, size_t size, const char *format, ...)  __attribute__ ((format (printf, 3, 4)));
int cul_asprintf(char **str, const char *format, ...)  __attribute__ ((format (printf, 2, 3)));

/* viof stream and string functions */

static inline int cul_vprintf(const char *format, va_list ap);
int cul_vprintf_stream(const char *format, va_list ap);
static inline int cul_vfprintf(FILE *stream, const char *format, va_list ap);
static inline int cul_vfscanf(FILE *stream, const char *format, va_list ap);

static inline int cul_vsprintf(char *str, const char *format, va_list ap);
static inline int cul_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int cul_vasprintf(char **str, const char *format, va_list ap);

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

static inline int cul_vsprintf(char *str, const char *format, va_list ap) {
	return vsprintf(str, format, ap);
}

static inline int cul_vsnprintf(char *str, size_t size, const char *format, va_list ap) {
	return vsnprintf(str, size, format, ap);
}

#endif /* CUL_IOF_H */
