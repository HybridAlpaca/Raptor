#include "Kernel.h"

#include <iostream>

using namespace Core;

Kernel::Kernel (unsigned int threadCount)
: stop (false)
, taskCount (0)
{
	std::cout << "[Kernel] Starting kernel with " << threadCount << " microkernels" << '\n';

	for (unsigned int i = 0; i < threadCount; ++i)
	{
		workers.emplace_back([this, i]() -> void
		{
			std::cout << "[Kernel] Starting MicroKernel " << i << '\n';

			while (true)
			{
				Task * task;

				{
					std::unique_lock<std::mutex> lock(mutex);

					condition.wait(lock, [this]() -> bool
					{
						// Wait until we have a task to execute

						return !taskQueue.empty() || stop;
					});

					if (stop && taskQueue.empty())
					{
						// Exit if the stop flag is set

						break;
					}

					// We have a task, pop it from the queue

					task = std::move(taskQueue.front());
					taskQueue.pop();
				}

				// Execute task

				task();
				--taskCount;
			}

			std::cout << "[Kernel] Destroying MicroKernel " << i << '\n';
		});
	}
}

Kernel::~Kernel ()
{
	stop = true;
	condition.notify_all();

	for (auto & worker : workers)
	{
		worker.join();
	}

	std::cout << "[Kernel] Destroying kernel" << '\n';
}

void Kernel::Schedule (const Task & task)
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		taskQueue.push(task);
	}

	++taskCount;
	condition.notify_one();
}

void Kernel::Wait () const
{
	while (taskCount > 0)
	{
		std::this_thread::yield();
	}
}
