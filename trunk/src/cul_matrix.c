#include <cul/cul_global.h>
#include <cul/cul_stream.h>
#include <cul/cul_base.h>
#include <cul/cul_vector.h>
#include <cul/cul_matrix.h>

#define TEMPLATE_CUL_CHAR
#include "templates_on.h"
#include "cul_matrix-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_CHAR

#define TEMPLATE_CUL_DOUBLE
#include "templates_on.h"
#include "cul_matrix-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_DOUBLE

#define TEMPLATE_CUL_INT
#include "templates_on.h"
#include "cul_matrix-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_INT
