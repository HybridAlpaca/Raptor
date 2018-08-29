#pragma once

#include "Platform.h"

// pointer types

#if RPTR_ENV_64
using uintptr		= unsigned long;	///< max value of pointer (64-bit)
#else
using uintptr		= unsigned int;		///< max value of pointer (32-bit)
#endif

// miscellaneous

using cchar		= const char *;		///< pointer to const char
using byte		= signed char;		///< byte
using ubyte		= unsigned char;	///< unsigned byte

// ints

using int8		= signed char;		///< 8-bit int
using int16		= signed short;		///< 16-bit int
using int32		= signed int;			///< 32-bit int
using int64		= signed long;		///< 64-bit int

// unsigned ints

using uint8		= unsigned char;	///< 8-bit unsigned int
using uint16	= unsigned short;	///< 16-bit unsigned int
using uint32	= unsigned int;		///< 32-bit unsigned int
using uint64	= unsigned long;	///< 64-bit unsigned int
