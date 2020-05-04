#pragma once

#include "Required.h"

/**
 *
 * @file String.h
 * @author Seth Traman
 *
 * @brief Provides an API for working with constant, compile-time string expressions and literals
 *
 **/

namespace Std
{
	/**
	 * @class StringLiteral
	 * @author Seth Traman
	 *
	 * @brief A compile-time constant container for referencing a string literal
	 *
	 * @tparam N The number of characters in the literal, not counting the null-terminator
	 *
	 **/

	template <uint32 N>
	class StringLiteral
	{
		/// Linear data buffer that references literal
		const char (& data) [N + 1];

	public:

		constexpr StringLiteral (const char (& str) [N + 1])
		: data (str)
		{}

		/// Access the internal buffer of characters
		constexpr inline cchar Data () const { return data; }

		/// Access a character in the buffer given an integral index to it
		/// @return The character at the provided index
		constexpr inline char operator[] (uint32 index) const { return data[index]; }
	};

	/**
	 * @class StringArray
	 * @author Seth Traman
	 *
	 * @brief A compile-time constant container for storing an array of characters
	 *
	 * @tparam N The number of characters in the array, not counting the null-terminator
	 *
	 **/

	template <uint32 N>
	class StringArray
	{
		/// Linear data buffer that stores characters
		char array [N + 1] {};

	public:

		template <uint32 N1>
		constexpr StringArray (const StringLiteral<N1> & s1, const StringLiteral<N - N1> & s2)
		{
			for (uint32 i = 0; i < N1; ++i)
			{
				array[i] = s1[i];
			}

			for (uint32 i = 0; i < N - N1; ++i)
			{
				array[N1 + i] = s2[i];
			}

			array[N] = '\0';
		}

		/// Access the internal buffer of characters
		constexpr inline cchar Data () const { return array; }

		/// Access a character in the buffer given an integral index to it
		/// @return The character at the provided index
		constexpr inline char operator[] (uint32 index) const { return array[index]; }
	};


	/// Operator for concatenating two StringLiterals into a StringArray
	/// @return A StringArray storing the data provided in the two literals

	template <uint32 N1, uint32 N2>
	constexpr auto operator+ (const StringLiteral<N1> & s1, const StringLiteral<N2> & s2)
	-> StringArray<N1 + N2>
	{
		return StringArray<N1 + N2>(s1, s2);
	}

	/// Convenience function for creating a string literal without specifying character count
	/// @return A StringLiteral referencing the provided string

	template <uint32 N>
	constexpr auto String (const char (& str) [N]) -> StringLiteral<N - 1>
	{
		return StringLiteral<N - 1>(str);
	}
}
