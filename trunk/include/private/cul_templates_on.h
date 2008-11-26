#if defined(TEMPLATE_CHAR)
    #define LOWER  c
    #define UPPER  C
    #define ATOM   char
    #define EMPTY  0
#elif defined(TEMPLATE_INT)
    #define LOWER  i
    #define UPPER  I
    #define ATOM   int
    #define EMPTY  0
#elif defined(TEMPLATE_DOUBLE)
    #define LOWER  d
    #define UPPER  D
    #define ATOM   double
    #define EMPTY  NAN
#elif defined(TEMPLATE_SIZE_T)
    #define LOWER  u
    #define UPPER  U
    #define ATOM   size_t
    #define EMPTY  0
#elif defined(TEMPLATE_CUL_PTR)
    #define LOWER  p
    #define UPPER  P
    #define ATOM   cul_ptr
    #define EMPTY  NULL
#else
    #error TEMPLATE_* directive undifined!
#endif

#define CONCAT2x(a1, a2)         a1 ## a2
#define CONCAT2(a1, a2)          CONCAT2x(a1, a2)
#define CONCAT3x(a1, a2, a3)     a1 ## a2 ## a3
#define CONCAT3(a1, a2, a3)      CONCAT3x(a1, a2, a3)
#define CONCAT4x(a1, a2, a3, a4) a1 ## a2 ## a3 ## a4
#define CONCAT4(a1, a2, a3, a4)  CONCAT4x(a1, a2, a3, a4)
#define CONCATEX2x(a1, a2)       a1 ## _ ## a2
#define CONCATEX2(a1,a2)         CONCATEX2x(a1, a2)

#define FUNCTION(base)           CONCAT2(CONCATEX2(cul, LOWER), base)
#define PFUNCTION(base)          CONCAT3(_, CONCATEX2(cul, LOWER), base)
#define TYPE(base)               CONCAT3(Cul, UPPER, base)
#define VIEW(base)               CONCAT4(Cul, UPPER, base, View)

