#include <cul/cul_global.h>
#include "cul_sort_prv.h"

#define TEMPLATE_CHAR
#include "cul_templates_on.h"
#include "cul_sort_prv-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CHAR

#define TEMPLATE_DOUBLE
#include "cul_templates_on.h"
#include "cul_sort_prv-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_DOUBLE

#define TEMPLATE_INT
#include "cul_templates_on.h"
#include "cul_sort_prv-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_INT

#define TEMPLATE_SIZE_T
#include "cul_templates_on.h"
#include "cul_sort_prv-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_SIZE_T

#define TEMPLATE_CUL_PTR
#include "cul_templates_on.h"
#include "cul_sort_prv-template.c"
#include "cul_templates_off.h"
#undef  TEMPLATE_CUL_PTR

