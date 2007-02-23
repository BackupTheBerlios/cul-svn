#if !defined(CUL_STREAM_H)
#define CUL_STREAM_H

#include <cul/cul_global.h>
#include <stdio.h>

/* global cul library io stream for printing */

FILE *cul_stream_get(void);
FILE *cul_stream_set(FILE *stream);
FILE *cul_stream_default(void);

/* io wrappers */

static inline FILE *cul_fopen(const char *filename, const char *mode);
static inline int cul_fflush(FILE *stream);
static inline int cul_fclose(FILE *stream);

static inline int cul_feof(FILE *stream);
static inline char *cul_fgets(char *str, int size, FILE *stream);
static inline int cul_fgetc(FILE *stream);
static inline int cul_fputs(char *str, FILE *stream);
static inline int cul_fputc(int character, FILE *stream);

/* implementations */

static inline FILE *cul_fopen(const char *filename, const char *mode) {
	return fopen(filename, mode);
}

static inline int cul_fflush(FILE *stream) {
	return fflush(stream);
}

static inline int cul_fclose(FILE *stream) {
	return fclose(stream);
}

static inline int cul_feof(FILE *stream) {
	return feof(stream);
}

static inline char *cul_fgets(char *str, int size, FILE *stream) {
	return fgets(str, size, stream);
}

static inline int cul_fgetc(FILE *stream) {
	return fgetc(stream);
}

static inline int cul_fputs(char *str, FILE *stream) {
	return fputs(str, stream);
}

static inline int cul_fputc(int character, FILE *stream) {
	return fputc(character, stream);
}

#endif
