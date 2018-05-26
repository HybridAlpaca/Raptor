#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <string>

// misc

typedef std::size_t size_t;
typedef std::intptr_t intptr;
typedef std::nullptr_t nullptr_t;
typedef std::string string;
typedef const char * cchar;

// signed ints

typedef std::int_fast8_t int8;
typedef std::int_fast16_t int16;
typedef std::int_fast32_t int32;
typedef std::int_fast64_t int64;
typedef std::intmax_t intmax;

// unsigned ints

typedef std::int_fast8_t uint8;
typedef std::int_fast16_t uint16;
typedef std::int_fast32_t uint32;
typedef std::int_fast64_t uint64;
typedef std::uintmax_t uintmax;

// atomics

typedef std::atomic_bool bool_a;

typedef std::atomic_int_fast8_t int8_a;
typedef std::atomic_int_fast16_t int16_a;
typedef std::atomic_int_fast32_t int32_a;
typedef std::atomic_int_fast64_t int64_a;

typedef std::atomic_int_fast8_t uint8_a;
typedef std::atomic_int_fast16_t uint16_a;
typedef std::atomic_int_fast32_t uint32_a;
typedef std::atomic_int_fast64_t uint64_a;
