#pragma once

#include "Required.h"

namespace Raptor
{
	template <typename T>
	struct Vector3
	{
		T x {};
		T y {};
		T z {};

		/// Constructor with scalar values
		Vector3 (T x, T y, T z) : x (x), y (y), z (z) {}

		/// Constructor with array of values
		Vector3 (T values [3]) : x (values[0]), y (values[1]), z (values[2]) {}

		/// Assignment to vector
		Vector3<T> operator= (const Vector3<T> & rhs)
		{
			if (rhs == (* this)) return (* this);
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return (* this);
		}

		/// Assignment to array
		Vector3<T> operator= (T rhs [3])
		{
			x = rhs[0];
			y = rhs[1];
			z = rhs[2];
			return (* this);
		}

		/// Assignment to scalar
		Vector3<T> operator= (const T & rhs)
		{
			x = y = z = rhs;
			return (* this);
		}

		/// Equality with vector
		bool operator== (const Vector3<T> & rhs) const
		{
			return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
		}

		/// Equality with array
		bool operator== (T rhs [3]) const
		{
			return (x == rhs[0]) && (y == rhs[1]) && (z == rhs[2]);
		}

		/// Inequality with vector
		bool operator!= (const Vector3<T> & rhs) const
		{
			return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
		}

		/// Inequality with array
		bool operator!= (T rhs [3]) const
		{
			return (x != rhs[0]) || (y != rhs[1]) || (z != rhs[2]);
		}

		/// Array access of values
		T & operator[] (uint32 idx) const
		{
			return (idx == 0) ? x : (idx == 1) ? y : z;
		}
	};

	using Vector3f = Vector3<float32>;
	using Vector3s = Vector3<uint16>;
	using Vector3i = Vector3<uint32>;
}
