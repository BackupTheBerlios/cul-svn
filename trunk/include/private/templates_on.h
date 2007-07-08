#if defined(TEMPLATE_CUL_CHAR)
	#define FUNC_GEN  c
	#define TYPE_GEN  C
	#define ATOM      char
	#define ATOM_EX   double
#elif defined(TEMPLATE_CUL_INT)
	#define FUNC_GEN  i
	#define TYPE_GEN  I
	#define ATOM      int
	#define ATOM_EX   double
#elif defined(TEMPLATE_CUL_DOUBLE)
	#define FUNC_GEN  d
	#define TYPE_GEN  D
	#define ATOM      double
	#define ATOM_EX   double
#elif defined(TEMPLATE_CUL_SIZE)
	#define FUNC_GEN  u
	#define TYPE_GEN  U
	#define ATOM      size_t
	#define ATOM_EX   double
#elif defined(TEMPLATE_CUL_PTR)
	#define FUNC_GEN  p
	#define TYPE_GEN  P
	#define ATOM      cul_ptr
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

#define FUNCTION(function_t)     CONCAT2(CONCATEX2(cul, FUNC_GEN), function_t)
#define PFUNCTION(function_t)    CONCAT3(_, CONCATEX2(cul, FUNC_GEN), function_t)
#define TYPE(t_name)             CONCAT3(Cul, TYPE_GEN, t_name)
#define VIEW(v_name)             CONCAT4(Cul, TYPE_GEN, v_name, View)

#define STRING(string)   #string
#define NAME(class_name) STRING(TYPE(class_name))

