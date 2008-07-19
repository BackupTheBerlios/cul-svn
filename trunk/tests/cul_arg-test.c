#include <cul/cul_global.h>
#include <cul/cul_arg.h>
#include <cul/cul_str.h>
#include <cul/cul_str_type.h>

#include <string.h>
#include <stdlib.h>

typedef struct cul_test_values {
	cul_bool _true;
	cul_bool _false;
	int _count;
	char *_str;
	char **_strv;
	int _int;

} cul_test_values;

/* global structure for command line argument values */
static cul_test_values values = {0, };

void cul_test_values_reset(cul_test_values *self);

CulArg options[] = {
	{ CUL_ARG_TRUE,       't',  "true", NULL, &values._true },
	{ CUL_ARG_FALSE,      'f', "false", NULL, &values._false },
	{ CUL_ARG_COUNT,      'c', "count", NULL, &values._count },
	{ CUL_ARG_STR,        's',   "str", NULL, &values._str },
	{ CUL_ARG_STRV,       'v',  "strv", NULL, &values._strv },
	{ CUL_ARG_INT,        'i',   "int", NULL, &values._int },
	{ CUL_ARG_TRUE_EX(0), '1',  "ex-1", NULL, NULL },
	{ CUL_ARG_TRUE_EX(0), '2',  "ex-2", NULL, NULL },
	{ CUL_ARG_TRUE_EX(1), '3',  "ex-3", NULL, NULL },
	{ CUL_ARG_TRUE_EX(1), '4',  "ex-4", NULL, NULL },
	CUL_ARG_NULL_DEFAULT
};

CulArg options_need[] = {
};

int main(int argc, char* argv[]) {
	cul_errno error;

	{ /* test simple flags */
		char *cmd[] = { "cul_arg-test", "-tc", "-c", "--count"}, **arg = cmd;
		int args = sizeof(cmd) / sizeof(*cmd);
		CulArg *table = options;

		/* reset values for test */
		cul_test_values_reset(&values);

		CUL_MESSAGE("Simple flags test...\n");
		CUL_ASSERT( !(error = cul_arg_parse(&args, &arg, &table)) );
		CUL_ASSERT( values._count == 3 && values._true );
	}

	{ /* test simple arguments */
		char *strv[] = { "strv1", "strv2", NULL };
		char *cmd[] = { "cul_arg-test", "-s", "str1", "--str", "str2", "--strv", "strv1", "-v", "strv2", "-i", "10"}, **arg = cmd;
		int args = sizeof(cmd) / sizeof(*cmd);
		CulArg *table = options;

		/* reset values for test */
		cul_test_values_reset(&values);

		CUL_MESSAGE("Simple argument test...\n");
		CUL_ASSERT( !(error = cul_arg_parse(&args, &arg, &table)) );
		CUL_ASSERT( !strcmp(values._str, "str2") && values._int == 10 );
		CUL_ASSERT( !cul_strv_cmp(values._strv, strv) );
	}

	{ /* test exclusive flags */
	}

	{ /* test position */
	}

	cul_arg_free(options);
	return 0;
}

void cul_test_values_reset(cul_test_values *self) {
	self->_true = CUL_FALSE;
	self->_false = CUL_TRUE;
	self->_count = 0;

	free( self->_str );
	self->_str = NULL;
	self->_int = 0;
}

