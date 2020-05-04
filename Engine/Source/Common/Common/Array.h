#pragma once

#include "Required.h"

namespace Std
{
	/**
	 * @struct Array
	 * @author Seth Traman
	 *
	 * @brief Zero-overhead aggregate over native C arrays, providing several utility methods evaluated at compile time.
	 *
	 * @tparam T The type of each element in the array
	 * @tparam N The number of elements to be stored
	 *
	 **/

	template <typename T, uint32 N>
	struct Array
	{
		/// @typedef Type The type of data stored in the array
		using Type = T;

		/// @typedef LValue l-value reference to Type
		using LValue = T &;

		/// @typedef ConstLValue Constant l-value reference to Type
		using ConstLValue = const T &;

		/// @typedef RValue r-value reference to Type
		using RValue = T &&;

		/// @typedef Pointer Pointer to Type
		using Pointer = T *;

		/// @typedef ConstPointer Constant pointer to Type
		using ConstPointer = const T * ;

		/// Buffer of data to be stored
		Type data[N];

		/// Constant element access operator
		constexpr inline ConstLValue operator[] (uint32 index) const { return data[index]; }

		/// Element access operator
		constexpr inline LValue operator[] (uint32 index) { return data[index]; }

		/// Constant bounds-checking access operator
		constexpr inline ConstLValue At (uint32 index) const { return data[index]; }

		/// Bounds-checking access operator
		constexpr inline LValue At (uint32 index) { return data[index]; }

		/// Constant iterator to first element
		constexpr inline ConstPointer Begin () const { return & data[0]; }

		/// Iterator to first element
		constexpr inline Pointer Begin () { return & data[0]; }

		/// Constant iterator to last element
		constexpr inline ConstPointer End () const { return & data[N - 1]; }

		/// Iterator to last element
		constexpr inline Pointer End () { return & data[N - 1]; }

		/// Constant reference to first element
		constexpr inline ConstLValue Front () const { return data[0]; }

		/// Reference to first element
		constexpr inline LValue Back () { return data[N - 1]; }

		/// Size of the array
		/// @return uint32 Size of the array
		constexpr inline uint32 Size () const { return N; }
	};
}
