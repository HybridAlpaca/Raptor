#pragma once

#include <Common/Required.h>
#include <Task.h>

#include <atomic>
#include <mutex>

namespace Kernel
{
	struct WorkQueue
	{
		static const uint32 MASK = Task::MAX_TASKS - 1u;

		std::mutex criticalSection;

		Task   taskPool  [Task::MAX_TASKS]; /// Free list of empty tasks
		Task * taskQueue [Task::MAX_TASKS]; /// List of tasks queue'd for execution

		uint32 front;
		uint32 back;
		uint32 taskCount;

		/// Atomic number of tasks waiting to be executed
		std::atomic<uint32> pending;

		WorkQueue ()
		{
			taskCount = 0;
			pending = 0;
			front = 0;
			back = 0;
		}

		~WorkQueue () {}

		Task * Allocate()
		{
			uint32 index = ++taskCount;
			return & taskPool[index & (Task::MAX_TASKS - 1u)];
		}

		void Push (Task * task)
		{
			std::lock_guard<std::mutex> lock{criticalSection};

			taskQueue[back & MASK] = task;
			++back;
			++pending;
		}

		Task * Pop ()
		{
			std::lock_guard<std::mutex> lock{criticalSection};

			const uint32 jobCount = back - front;

			if (jobCount <= 0)
			{
				// No available jobs
				return nullptr;
			}

			--back;

			return taskQueue[back & MASK];
		}

		inline uint32 JobCount () const
		{
			return (back - front);
		}

		inline bool HasPending () const
		{
			return (pending != 0);
		}

		inline bool Empty () const
		{
			return (front == 0 && back == 0);
		}
	};
}
