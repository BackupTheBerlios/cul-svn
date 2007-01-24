#include <cul/cul_global.h>
#include <cul/cul_base_common.h>

int cul_fscanf_skip_line(FILE *stream) {
	int result;
	result = fscanf(stream, "%*[^\n]%*1[\n]");
	return result;
}
