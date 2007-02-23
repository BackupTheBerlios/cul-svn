#if !defined(CUL_FILE_H)
#define CUL_FILE_H

#include <cul/cul_global.h>

cul_bool cul_file_readable(const char *filename);
cul_bool cul_file_writeable(const char *filename);

size_t cul_file_lines(const char *filename);
cul_errno cul_file_read_lines(const char *filename, size_t size, char ***contents, size_t *lines);
cul_errno cul_file_write_lines(const char *filename, char **contents);

#endif
