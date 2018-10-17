#pragma once

namespace Std
{
	template <class T>
	struct RemoveReference { using Type = T; };

	template <class T>
	struct RemoveReference<T &> { using Type = T; };

	template <class T>
	struct RemoveReference<T &&> { using Type = T; };

	template <typename T>
  constexpr inline typename RemoveReference<T>::Type && Move (T && t)
  {
		return static_cast<typename RemoveReference<T>::Type &&>(t);
	}
}
