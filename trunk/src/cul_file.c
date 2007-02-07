#include <cul/cul_file.h>
#include <cul/cul_list.h>

cul_bool cul_file_readable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = cul_fopen(filename, "r")) == NULL )
		return CUL_FALSE;
	cul_fclose(fid);
	return CUL_TRUE;
}

cul_bool cul_file_writeable(const char *filename) {
	FILE *fid;

	if( filename == NULL || (fid = cul_fopen(filename, "w")) == NULL )
		return CUL_FALSE;
	cul_fclose(fid);
	return CUL_TRUE;
}

size_t cul_file_lines(const char *filename) {
	CUL_UNUSED(filename);
	CUL_ERROR_ERRNO_RET_VAL(0, CUL_ESTUB);
}

cul_errno cul_file_read_lines(const char *filename, size_t size, char ***contents, size_t *lines) {
	if( filename == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EINVAL, CUL_EINVAL);

	FILE *stream = cul_fopen(filename, "r");
	if( stream == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EFACCESS, CUL_EFACCESS);

	/* initialize list */
	CulList *list = NULL;

	/* initialize output data */
	*contents = NULL;
	*lines = 0;

	/* read file */
	size_t list_size = 0;
	while( !cul_feof(stream) ) {
		char buffer[size];

		if( !cul_fgets(buffer, size, stream) ) {
			if( cul_feof(stream) )
				break;
			CUL_ERROR_ERRNO_RET_VAL(CUL_EFIO, CUL_EFIO);
		}

		size_t buffer_size = cul_strlen(buffer);

		/* strip new line character at the end */
		if( buffer[buffer_size-1] == CUL_STR_NEWLINE )
			cul_strnull(buffer + (--buffer_size));

		char *data = cul_strdup_size(buffer, buffer_size);
		CulList *node = cul_list_insert_next(list, data);
		if( node == NULL || data == NULL ) {
			cul_list_free_all(cul_list_first(list), cul_free);
			if( node == NULL )
				cul_free(data);

			cul_fclose(stream);
			CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
		}

		/* insert list node */
		list = node;
		list_size += 1;
	}

	char **linesv = cul_malloc( (list_size+1)*sizeof(char *) );
	if( linesv == NULL ) {
		/* clean */
		cul_list_free_all(cul_list_first(list), cul_free);
		cul_fclose(stream);
		CUL_ERROR_ERRNO_RET_VAL(CUL_ENOMEM, CUL_ENOMEM);
	}

	/* set output variables */
	*contents = linesv;
	*lines = list_size;

	/* copy data, we are currently at the end of the list */
	linesv[list_size] = NULL;
	for( CulList *node = list; list_size--; node = cul_list_prev(node) )
		linesv[list_size] = node->data;

	/* remove temporary data */
	cul_list_free_all(cul_list_first(list), NULL);
	cul_fclose(stream);

	return CUL_SUCCESS;
}

cul_errno cul_file_write_lines(const char *filename, char **contents) {
	CUL_UNUSED(contents);
	if( filename == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EINVAL, CUL_EINVAL);

	FILE *fid = cul_fopen(filename, "w");
	if( fid == NULL )
		CUL_ERROR_ERRNO_RET_VAL(CUL_EFACCESS, CUL_EFACCESS);
	cul_fclose(fid);

	CUL_ERROR_ERRNO_RET_VAL(CUL_ESTUB, CUL_ESTUB);
}
