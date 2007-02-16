#if !defined(CUL_FILE_H)
#define CUL_FILE_H

#include <cul/cul_global.h>
#include <cul/cul_str.h>

#include <stdio.h>

static inline FILE *cul_fopen(const char *filename, const char *mode);
static inline int cul_fflush(FILE *stream);
static inline int cul_fclose(FILE *stream);

static inline int cul_feof(FILE *stream);
static inline char *cul_fgets(char *str, int size, FILE *stream);
static inline int cul_fputs(char *str, FILE *stream);

cul_bool cul_file_readable(const char *filename);
cul_bool cul_file_writeable(const char *filename);

size_t cul_file_lines(const char *filename);
cul_errno cul_file_read_lines(const char *filename, size_t size, char ***contents, size_t *lines);
cul_errno cul_file_write_lines(const char *filename, char **contents);

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

static inline int cul_fputs(char *str, FILE *stream) {
	return fputs(str, stream);
}

#endif
