
#include "../config.h"

#ifdef _MSC_VER
#undef HAVE_SYS_TIME_H
#undef HAVE_UNISTD_H
#undef HAVE_COMPUTED_GOTO
#undef HAVE_TGMATH_H
#define __x86_64
#define __amd64__

#pragma warning(disable:4996)
#pragma warning(disable:4146)

#include <intrin.h>
#include <ymath.h>
#define	jit_float32_nan	((jit_float32)(_Nan._Float))
#define	jit_float64_nan	((jit_float64)(_Nan._Double))
#define	jit_nfloat_nan	((jit_nfloat)(_Nan._Double))
#endif

