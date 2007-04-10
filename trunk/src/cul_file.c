#include <cul/cul_file.h>

#include <cul/cul_io.h>
#include <cul/cul_str.h>
#include <cul/cul_list.h>
#include <cul/cul_string.h>

cul_bool cul_file_readable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = cul_fopen(filename, "r")) == NULL )
		return CUL_FALSE;
	cul_fclose(fid);
	return CUL_TRUE;
}

cul_bool cul_file_writeable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = cul_fopen(filename, "r+")) == NULL )
		return CUL_FALSE;
	cul_fclose(fid);
	return CUL_TRUE;
}

size_t cul_file_lines(const char *filename) {
	CUL_UNUSED(filename);
	CUL_ERROR_ERRNO_RET_VAL(0, CUL_ESTUB);
}


cul_errno cul_file_read(const char *filename, char ***contents, size_t *lines) {
	CulList *line = NULL;
	size_t line_size = 0;

	char buffer[BUFSIZ];           /* buffer for data reading */
	size_t buffer_size = 0;        /* number of single line characters in buffer */

	char *data = NULL;
	size_t data_size = 0;

	cul_bool is_eof, is_token;

	if( filename == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EINVAL, CUL_EINVAL);

	FILE *stream = cul_fopen(filename, "r");
	if( stream == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EFACCESS, CUL_EFACCESS);

	/* initialize output data */
	*contents = NULL;
	*lines = 0;

	/* read file */
	is_eof = cul_feof(stream);
	while( !is_eof ) {
		CulList *node;
		char *token = buffer, *next, *string;
		size_t size;

		buffer_size = cul_fread(buffer, sizeof(char), BUFSIZ, stream);
		is_eof = cul_feof(stream);                    /* refresh eof state */

		/* check for read error */
		if( buffer_size != BUFSIZ && !is_eof ) {
			cul_fclose(stream); cul_free(data);
			cul_list_free_all(cul_list_first(line), cul_free);
			CUL_ERROR_ERRNO_RET_VAL(CUL_EFIO, CUL_EFIO);
		}

		is_token = (next = cul_memchr(token, CUL_STR_NEWLINE, buffer_size)) != NULL;
		size = is_token? (size_t)(next - token): buffer_size;

		if( (string = cul_malloc((data_size + size + 1)*sizeof(char))) == NULL ) {
			cul_fclose(stream); cul_free(data);
			cul_list_free_all(cul_list_first(line), cul_free);
			CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
		}

		cul_memcpy(string, data, data_size);         /* copy previous data */
		cul_memcpy(string+data_size, token, size);   /* copy token */
		cul_strnull(string+data_size+size);
		cul_free(data);                              /* free previous data */

		if( is_token || is_eof ) {
			if( (node = cul_list_insert_next(line, string)) == NULL ) {
				cul_fclose(stream);
				cul_list_free_all(cul_list_first(line), cul_free); cul_free(string);
				CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
			}
			line = node;
			line_size += 1;
			if( !is_token )
				break;
		} else {
			data = string;
			data_size += size;
			continue;
		}

		buffer_size -= size+1;
		token = next + 1;

		while( CUL_TRUE ) {
			is_token = (next = cul_memchr(token, CUL_STR_NEWLINE, buffer_size)) != NULL;
			size = is_token? (size_t)(next - token): buffer_size;

			if( (string = cul_malloc((size + 1)*sizeof(char))) == NULL ) {
				cul_fclose(stream);
				cul_list_free_all(cul_list_first(line), cul_free);
				CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
			}

			cul_memcpy(string, token, size);    /* copy token */
			cul_strnull(string+size);

			if( is_token || is_eof ) {
				if( (node = cul_list_insert_next(line, string)) == NULL ) {
					cul_fclose(stream); cul_free(string);
					cul_list_free_all(cul_list_first(line), cul_free);
					CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
				}
				line = node;
				line_size += 1;

				if( !is_token )
					break;
			}
			else {
				data = string;
				data_size = size;
				break;
			}

			buffer_size -= size+1;
			token = next + 1;
		}
	}

	char **linesv = cul_malloc( (line_size+1)*sizeof(char *) );
	if( linesv == NULL ) {
		cul_fclose(stream);
		cul_list_free_all(cul_list_first(line), cul_free);
		CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
	}

	/* set output variables */
	*contents = linesv;
	*lines = line_size;

	/* copy data, we are currently at the end of the list */
	linesv[line_size] = NULL;
	for( CulList *node = line; line_size--; node = cul_list_prev(node) )
		linesv[line_size] = node->data;

	/* remove temporary data */
	cul_list_free_all(cul_list_first(line), NULL);

	cul_fclose(stream);
	return CUL_SUCCESS;
}

cul_errno cul_file_write(const char *filename, char **contents) {
	CUL_UNUSED(contents);
	if( filename == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EINVAL, CUL_EINVAL);

	FILE *stream = cul_fopen(filename, "w");
	if( stream == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EFACCESS, CUL_EFACCESS);

	/* write contents if present */
	if( contents != NULL ) {
		const size_t lines = cul_strv_size(contents);
		for( size_t i=0; i<lines; ++i) {
			if( cul_fputs(contents[i], stream) < 0 )
				CUL_ERROR_ERRNO_RET_VAL(CUL_EFIO, CUL_EFIO);
			if( cul_fputc(CUL_STR_NEWLINE, stream) == EOF )
				CUL_ERROR_ERRNO_RET_VAL(CUL_EFIO, CUL_EFIO);
		}
	}

	cul_fclose(stream);
	return CUL_SUCCESS;
}
