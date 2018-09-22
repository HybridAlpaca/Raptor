#pragma once

namespace Raptor
{
	template <class L, class R>
	class Either
	{
		bool isLeft;

		union
		{
			L left;
			R right;
		};

	public:

		Either<L, R> (L value)
		{
			left = value;
			isLeft = true;
		}

		Either<L, R> (R value)
		{
			right = value;
			isLeft = false;
		}

		template <typename F>
		constexpr Either<L, R> MapLeft (const F & function)
		{
			if (isLeft)
				function(left);

			return (* this);
		}

		template <typename F>
		constexpr Either<L, R> MapRight (const F & function)
		{
			if (!isLeft)
				function(right);

			return (* this);
		}

		bool Join ()
		{
			return isLeft;
		}
	};
}
