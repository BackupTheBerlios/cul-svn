#include <cul/cul_file.h>

#include <cul/cul_str.h>
#include <cul/cul_list.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

cul_bool cul_file_readable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = fopen(filename, "r")) == NULL )
		return CUL_FALSE;
	fclose(fid);
	return CUL_TRUE;
}

cul_bool cul_file_writeable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = fopen(filename, "r+")) == NULL )
		return CUL_FALSE;
	fclose(fid);
	return CUL_TRUE;
}

size_t cul_file_lines(const char *filename) {
	CUL_UNUSED(filename);
	/* TODO cul_file_lines stub */
	CUL_ERROR_ERRNO_RET(0, CUL_ESTUB);
}


cul_errno cul_file_read_strv(const char *filename, char ***contents, size_t *lines) {
	CulList *line = NULL;
	size_t line_size = 0;

	char buffer[BUFSIZ];           /* buffer for data reading */
	size_t buffer_size = 0;        /* number of single line characters in buffer */

	char *data = NULL;
	size_t data_size = 0;

	cul_bool is_eof, is_token;

	/* initialize output data */
	*contents = NULL;
	*lines = 0;

	if( filename == NULL )
		return CUL_SUCCESS;

	FILE *stream = fopen(filename, "r");
	if( stream == NULL )
		CUL_ERROR_ERRNO_RET(CUL_EFACCESS, CUL_EFACCESS);

	/* read file */
	is_eof = feof(stream);
	while( !is_eof ) {
		CulList *node;
		char *token = buffer, *next, *string;
		size_t size;

		buffer_size = fread(buffer, sizeof(char), BUFSIZ, stream);
		is_eof = feof(stream);                    /* refresh eof state */

		/* check for read error */
		if( buffer_size != BUFSIZ && !is_eof ) {
			fclose(stream); free(data);
			cul_list_free_all(cul_list_first(line), free);
			CUL_ERROR_ERRNO_RET(CUL_EFIO, CUL_EFIO);
		}

		is_token = (next = memchr(token, CUL_STR_NEWLINE, buffer_size)) != NULL;
		size = is_token? (size_t)(next - token): buffer_size;

		if( (string = malloc((data_size + size + 1)*sizeof(char))) == NULL ) {
			fclose(stream); free(data);
			cul_list_free_all(cul_list_first(line), free);
			CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
		}

		memcpy(string, data, data_size);         /* copy previous data */
		memcpy(string+data_size, token, size);   /* copy token */
		string[data_size+size] = CUL_STR_NULL;
		free(data);                              /* free previous data */

		if( is_token || is_eof ) {
			if( (node = cul_list_insert_next(line, string)) == NULL ) {
				fclose(stream); free(string);
				cul_list_free_all(cul_list_first(line), free);
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
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
			is_token = (next = memchr(token, CUL_STR_NEWLINE, buffer_size)) != NULL;
			size = is_token? (size_t)(next - token): buffer_size;

			if( (string = malloc((size + 1)*sizeof(char))) == NULL ) {
				fclose(stream);
				cul_list_free_all(cul_list_first(line), free);
				CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
			}

			memcpy(string, token, size);    /* copy token */
			string[size] = CUL_STR_NULL;

			if( is_token || is_eof ) {
				if( (node = cul_list_insert_next(line, string)) == NULL ) {
					fclose(stream); free(string);
					cul_list_free_all(cul_list_first(line), free);
					CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
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

	char **linesv = malloc( (line_size+1)*sizeof(char *) );
	if( linesv == NULL ) {
		fclose(stream);
		cul_list_free_all(cul_list_first(line), free);
		CUL_ERROR_ERRNO_RET(CUL_ENOMEM, CUL_ENOMEM);
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

	fclose(stream);
	return CUL_SUCCESS;
}

cul_errno cul_file_write_strv(const char *filename, char **contents) {
	if( filename == NULL )
		CUL_ERROR_ERRNO_RET(CUL_EINVAL, CUL_EINVAL);

	FILE *stream = fopen(filename, "w");
	if( stream == NULL )
		CUL_ERROR_ERRNO_RET(CUL_EFACCESS, CUL_EFACCESS);

	/* write contents if present */
	if( contents != NULL ) {
		const size_t lines = cul_strv_size(contents);
		for( size_t i=0; i<lines; ++i) {
			if( fputs(contents[i], stream) < 0 )
				CUL_ERROR_ERRNO_RET(CUL_EFIO, CUL_EFIO);
			if( fputc(CUL_STR_NEWLINE, stream) == EOF )
				CUL_ERROR_ERRNO_RET(CUL_EFIO, CUL_EFIO);
		}
	}

	fclose(stream);
	return CUL_SUCCESS;
}
