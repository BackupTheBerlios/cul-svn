#include <cul/cul_global.h>
#include <cul/cul_permute.h>

#define TEMPLATE_CUL_CHAR
#include "cul_templates_on.h"
#include "cul_permute-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_CHAR

#define TEMPLATE_CUL_DOUBLE
#include "cul_templates_on.h"
#include "cul_permute-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_DOUBLE

#define TEMPLATE_CUL_INT
#include "cul_templates_on.h"
#include "cul_permute-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_INT

#define TEMPLATE_CUL_SIZE
#include "cul_templates_on.h"
#include "cul_permute-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_SIZE

#define TEMPLATE_CUL_PTR
#include "cul_templates_on.h"
#include "cul_permute-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_PTR

