#include <cul/cul_global.h>
#include <cul/cul_permute.h>

#define TEMPLATE_CUL_CHAR
#include "templates_on.h"
#include "cul_permute-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_CHAR

#define TEMPLATE_CUL_DOUBLE
#include "templates_on.h"
#include "cul_permute-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_DOUBLE

#define TEMPLATE_CUL_INT
#include "templates_on.h"
#include "cul_permute-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_INT

#define TEMPLATE_CUL_SIZE
#include "templates_on.h"
#include "cul_permute-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_SIZE

#define TEMPLATE_CUL_PTR
#include "templates_on.h"
#include "cul_permute-template.c"
#include "templates_off.h"
#undef  TEMPLATE_CUL_PTR

