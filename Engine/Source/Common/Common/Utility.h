#pragma once

namespace Std
{
	template <class T>
	struct RemoveReference { using type = T; };

	template <class T>
	struct RemoveReference<T &> { using type = T; };

	template <class T>
	struct RemoveReference<T &&> { using type = T; };

	template <typename T>
  constexpr typename RemoveReference<T>::type && Move (T && t)
  {
		return static_cast<typename RemoveReference<T>::type &&>(t);
	}
}
