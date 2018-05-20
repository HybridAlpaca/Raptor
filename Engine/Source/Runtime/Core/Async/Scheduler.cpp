#include <Core/Common/Required.h>
#include "Scheduler.h"

#include <mutex>
#include <thread>

using Core::Async::Scheduler;

Scheduler::Scheduler (uint8 num_threads)
	: numWorkers(num_threads)
	, shouldStop(false)
	, task_count(0)
{
	for (uint8 i = 0; i < num_threads; i++)
	{
		// create a worker and tell it to
		// run WorkerTask
		workers.emplace_back(& Scheduler::WorkerTask, this);
	}
}

Scheduler::~Scheduler ()
{
	Destroy();
}

void Scheduler::Destroy ()
{
	shouldStop = true;
	condition.notify_all();

	for (auto & worker : workers)
	{
		// terminate each of the workers
		if (worker.joinable())
		{
			// check if the worker thread
			// is actually able to join
			// back with the main thread
			worker.join();
		}
	}
}

void Scheduler::Schedule (Task task)
{
	{
		std::unique_lock<std::mutex> lock(mutex);
		taskQueue.push(task);
	}
	
	++task_count;
	condition.notify_one();
}

void Scheduler::WaitAll ()
{
	while (task_count != 0)
	{
		// put the waiting thread to sleep
		// until all tasks are completed
		std::this_thread::yield();
	}
}

void Scheduler::WorkerTask ()
{

	while (true)
	{
		Task task;
		
		{
			std::unique_lock<std::mutex> lock(mutex);
			
			condition.wait(lock, [this]() ->
			bool {
				// put this thread to sleep until there
				// is a task to execute or the scheduler
				// has been told to stop
				return !taskQueue.empty() || shouldStop;
			});
			
			if (taskQueue.empty() && shouldStop)
			{
				// terminate if there are no more
				// tasks to execute and the scheduler
				// has been told to stop
				return;
			}
			
			task = std::move(taskQueue.front());
			taskQueue.pop();
		}
		
		task(nullptr);
		--task_count;
	}
}