#pragma once

using int8  = signed char;
using int16 = signed short;
using int32 = signed int;
using int64 = signed long long;

static_assert(sizeof(int8)  == 1, "Types must be valid widths");
static_assert(sizeof(int16) == 2, "Types must be valid widths");
static_assert(sizeof(int32) == 4, "Types must be valid widths");
static_assert(sizeof(int64) == 8, "Types must be valid widths");

using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

static_assert(sizeof(uint8)  == 1, "Types must be valid widths");
static_assert(sizeof(uint16) == 2, "Types must be valid widths");
static_assert(sizeof(uint32) == 4, "Types must be valid widths");
static_assert(sizeof(uint64) == 8, "Types must be valid widths");

using float32 = float;
using float64 = double;

static_assert(sizeof(float32) == 4, "Types must be valid widths");
static_assert(sizeof(float64) == 8, "Types must be valid widths");

using cchar = const char * const;
