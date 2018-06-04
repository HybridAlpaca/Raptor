#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>

// misc

using size_t = std::size_t;
using nullptr_t = std::nullptr_t;
using byte = std::byte;

// chars

using cchar = const char *;
using uchar = unsigned char *;

// signed ints

using int8 = std::int_fast8_t;
using int16 = std::int_fast16_t;
using int32 = std::int_fast32_t;
using int64 = std::int_fast64_t;
using intmax = std::intmax_t;

// unsigned ints

using uint = unsigned int;
using uint8 = std::uint_fast8_t;
using uint16 = std::uint_fast16_t;
using uint32 = std::uint_fast32_t;
using uint64 = std::uint_fast64_t;
using uintmax = std::uintmax_t;

// atomics

using bool_a = std::atomic_bool;

using int8_a = std::atomic_int_fast8_t;
using int16_a = std::atomic_int_fast16_t;
using int32_a = std::atomic_int_fast32_t;
using int64_a = std::atomic_int_fast64_t;

using uint8_a = std::atomic_int_fast8_t;
using uint16_a = std::atomic_int_fast16_t;
using uint32_a = std::atomic_int_fast32_t;
using uint64_a = std::atomic_int_fast64_t;
