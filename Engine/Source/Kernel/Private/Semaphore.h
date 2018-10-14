#pragma once

#include <condition_variable>
#include <mutex>

namespace Kernel
{
	class Semaphore
	{
		std::mutex              mutex;
		std::condition_variable condition;
		bool                    signal;

	public:

		Semaphore () : signal (false) {}
		Semaphore (const Semaphore & lvalue) = delete;

		Semaphore & operator= (const Semaphore & rhs) = delete;

		inline void Notify ()
		{
			std::unique_lock<std::mutex> lock{mutex};
			signal = true;
			condition.notify_all();
		}

		inline void Wait ()
		{
			std::unique_lock<std::mutex> lock{mutex};
			condition.wait(lock, [&]() { return signal; });
			signal = false;
		}
	};
}

