/*
 * jit-defs.h - Define the primitive numeric types for use by the JIT.
 *
 * Copyright (C) 2004  Southern Storm Software, Pty Ltd.
 *
 * The libjit library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * The libjit library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the libjit library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef	_JIT_DEFS_H
#define	_JIT_DEFS_H

#include <stdint.h>

#ifdef	__cplusplus
extern	"C" {
#endif

#ifdef _MSC_VER
#define JIT_EXPORT_DATA extern __declspec(dllimport)
#else
#define JIT_EXPORT_DATA extern
#endif

typedef int8_t jit_sbyte;
typedef uint8_t jit_ubyte;
typedef int16_t jit_short;
typedef uint16_t jit_ushort;
typedef int32_t jit_int;
typedef uint32_t jit_uint;
typedef intptr_t jit_nint;
typedef uintptr_t jit_nuint;
#if defined(__cplusplus) && defined(__GNUC__)
typedef long long jit_long;
typedef unsigned long long jit_ulong;
#else
typedef long long jit_long;
typedef unsigned long long jit_ulong;
#endif
typedef float jit_float32;
typedef double jit_float64;
typedef long double jit_nfloat;
typedef void *jit_ptr;

#define	JIT_NATIVE_INT64 1


#if defined(__cplusplus) && defined(__GNUC__)
#define	JIT_NOTHROW		throw()
#else
#define	JIT_NOTHROW
#endif

#define	jit_min_int		(((jit_int)1) << (sizeof(jit_int) * 8 - 1))
#define	jit_max_int		((jit_int)(~jit_min_int))
#define	jit_max_uint	((jit_uint)(~((jit_uint)0)))
#define	jit_min_long	(((jit_long)1) << (sizeof(jit_long) * 8 - 1))
#define	jit_max_long	((jit_long)(~jit_min_long))
#define	jit_max_ulong	((jit_ulong)(~((jit_ulong)0)))

#ifdef	__cplusplus
};
#endif

#endif /* _JIT_DEFS_H */
