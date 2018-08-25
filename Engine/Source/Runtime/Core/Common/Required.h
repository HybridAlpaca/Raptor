#pragma once

#if __GNUC__
#	if __x86_64__ || __ppc64__
#		define RPTR_ENV_64
		using psize = unsigned long;
#	else
#		define RPTR_ENV_32
		using psize = unsigned int;
#	endif
#endif

using cchar		= const char *;
using byte		= signed char;
using ubyte		= unsigned char;

using int8		= signed char;
using int16		= signed short;
using int32		= signed int;
using int64		= signed long;

using uint8		= unsigned char;
using uint16	= unsigned short;
using uint32	= unsigned int;
using uint64	= unsigned long;
