#pragma once

#include <vector>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>

namespace Core
{
	using Task = void ();

	class Kernel
	{
		std::vector<std::thread> workers;
		std::queue<Task *>       taskQueue;
		std::atomic_bool         stop;
		std::atomic_uint         taskCount;
		std::mutex               mutex;
		std::condition_variable  condition;

	public:

		Kernel (unsigned int threadCount);
		Kernel (const Kernel & other) = delete;
		~Kernel ();

		Kernel & operator= (const Kernel & rhs) = delete;

		void Schedule (const Task & task);

		void Wait () const;

		inline unsigned int TaskCount () const { return taskCount; }
	};
}
