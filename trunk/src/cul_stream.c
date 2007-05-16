#include <cul/cul_stream.h>

FILE *cul_stream_default = NULL;

static void init_cul_stream_init(void) __attribute__ ((constructor));
static void init_cul_stream_init(void) {
	cul_stream_default = cul_stream_get_default();
}

FILE *cul_stream_get(void) {
	return cul_stream_default;
}

FILE *cul_stream_get_default(void) {
	/* TODO possible environment variable read in future */
	return stderr;
}

FILE *cul_stream_set(FILE *stream) {
	FILE *old_stream = cul_stream_default;
	cul_stream_default = stream;
	return old_stream;
}
