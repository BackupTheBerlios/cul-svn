#include <cul/cul_io.h>

FILE *cul_stream = NULL;

void init_cul_stream(void) __attribute__ ((constructor));
void init_cul_stream(void) {
	cul_stream = cul_stream_default();
}

FILE *cul_stream_get(void) {
	return cul_stream;
}

FILE *cul_stream_set(FILE *stream) {
	FILE *old_stream = cul_stream;
	cul_stream = stream;
	return old_stream;
}

FILE *cul_stream_default(void) {
	return stderr;
}
