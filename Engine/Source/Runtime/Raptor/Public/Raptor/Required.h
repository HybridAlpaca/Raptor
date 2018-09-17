#pragma once

#include "Platform.h"

// pointer types

#if RPTR_ENV_64
	using uintptr		= unsigned long long;	///< max value of pointer (64-bit)
	static_assert(sizeof(uintptr) == (64 / 8), "Pointer int sizes should be 8 bytes on 64 bit machines");
#else
	using uintptr		= unsigned int;		///< max value of pointer (32-bit)
	static_assert(sizeof(uintptr) == (32 / 8), "Pointer int sizes should be 4 bytes on 32 bit machines");
#endif

// miscellaneous

using cchar		= const char *;		///< pointer to const char
using byte		= signed char;		///< byte
using ubyte		= unsigned char;	///< unsigned byte

// tests

static_assert(sizeof(byte)  == (8 / 8), "One byte should be eight bits");
static_assert(sizeof(ubyte) == (8 / 8), "One unsigned byte should be eight bits");

// ints

using int8		= signed char;		///< 8-bit int
using int16		= signed short;		///< 16-bit int
using int32		= signed int;			///< 32-bit int
using int64		= signed long long;		///< 64-bit int

// tests

static_assert(sizeof(int8)  == (8 / 8), "int8 should be eight bits");
static_assert(sizeof(int16) == (16 / 8), "int16 should be 16 bits");
static_assert(sizeof(int32) == (32 / 8), "int32 should be 32 bits");
static_assert(sizeof(int64) == (64 / 8), "int64 should be 64 bits");

// unsigned ints

using uint8		= unsigned char;	///< 8-bit unsigned int
using uint16	= unsigned short;	///< 16-bit unsigned int
using uint32	= unsigned int;		///< 32-bit unsigned int
using uint64	= unsigned long long;	///< 64-bit unsigned int

// tests

static_assert(sizeof(uint8)  == (8 / 8), "uint8 should be eight bits");
static_assert(sizeof(uint16) == (16 / 8), "uint16 should be 16 bits");
static_assert(sizeof(uint32) == (32 / 8), "uint32 should be 32 bits");
static_assert(sizeof(uint64) == (64 / 8), "uint64 should be 64 bits");

// floating point ints

using float32 = float;
using float64 = double;

// tests

static_assert(sizeof(float32) == (32 / 8), "Single precision floats should be 32 bits");
static_assert(sizeof(float64) == (64 / 8), "Double precision floats should be 64 bits");
