#include <cul/cul_global.h>
#include <cul/cul_stream.h>
#include <cul/cul_vector.h>
#include <cul/cul_matrix.h>
#include <cul_prv_copy.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TEMPLATE_CUL_CHAR
#include "cul_templates_on.h"
#include "cul_matrix-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_CHAR

#define TEMPLATE_CUL_DOUBLE
#include "cul_templates_on.h"
#include "cul_matrix-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_DOUBLE

#define TEMPLATE_CUL_INT
#include "cul_templates_on.h"
#include "cul_matrix-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_INT

#define TEMPLATE_CUL_SIZE
#include "cul_templates_on.h"
#include "cul_matrix-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_SIZE

