#pragma once

namespace Std
{
	/// Utility class for stripping references from a type
	template <class T>
	struct RemoveReference { using Type = T; };

	/// Utility class for stripping references from a type
	template <class T>
	struct RemoveReference<T &> { using Type = T; };

	/// Utility class for stripping references from a type
	template <class T>
	struct RemoveReference<T &&> { using Type = T; };

	/// Converts T into an rvalue reference for use with move semantics
	/// @tparam T The type to be converted into an rvalue reference
	/// @return An rvalue reference (T &&) to the value provided

	template <typename T>
  constexpr inline typename RemoveReference<T>::Type && Move (T && t)
  {
		return static_cast<typename RemoveReference<T>::Type &&>(t);
	}
}
