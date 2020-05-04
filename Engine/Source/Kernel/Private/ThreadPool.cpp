#include <ThreadPool.h>
#include "WorkerThread.h"

using namespace Kernel;

void ThreadPool::InitializeWorkers ()
{
	workerThreads = new WorkerThread [workerThreadCount];

	for (uint32 i = 0; i < workerThreadCount; ++i)
	{
		workerThreads[i].thread = std::thread(& ThreadPool::Worker, this, i);
	}
}

void ThreadPool::Worker (uint32 index)
{
	WorkerThread & worker = workerThreads[index];

	while (!shutdown)
	{
		Task * task = queue.Pop();

		if (!task)
		{
			worker.done.Notify();
			worker.wakeup.Wait();
		}
		else
		{
			RunTask(task);
		}
	}
}

void ThreadPool::RunTask (Task * task)
{
	WaitForChildren(task);

	// Run the actual piece of work associated with this task
	task -> function(task -> data);

	if (task -> parent)
	{
		// Decrease parent's pending child task counter
		--(task -> parent -> pending);
	}

	for (uint32 i = 0; i < task -> continuationCount; ++i)
	{
		// Queue up any continuations for execution
		queue.Push(task -> continuations[i]);
	}

	if (task -> pending > 0)
	{
		// Decrease this task's pending counter
		// (Remember, the task function itself counts as pending!)
		--(task -> pending);
	}

	if (queue.pending > 0)
	{
		--queue.pending;
	}
}

void ThreadPool::WaitForChildren (Task * task)
{
	while (task -> pending > 1)
	{
		Task * waitTask = queue.Pop();

		if (waitTask)
		{
			RunTask(waitTask);
		}
	}
}

ThreadPool::ThreadPool ()
{
	shutdown = false;

	logicalThreadCount = std::thread::hardware_concurrency();
	workerThreadCount  = logicalThreadCount - 1;

	InitializeWorkers();
}

ThreadPool::ThreadPool (uint32 workers)
{
	shutdown = false;

	logicalThreadCount = std::thread::hardware_concurrency();
	workerThreadCount  = workers;

	InitializeWorkers();
}

ThreadPool::~ThreadPool ()
{
	shutdown = true;

	for (uint32 i = 0; i < workerThreadCount; ++i)
	{
		workerThreads[i].Shutdown();
	}

	delete [] workerThreads;
}

Task * ThreadPool::Allocate ()
{
	Task * task = queue.Allocate();

	task -> pending = 1;
	task -> continuationCount = 0;
	task -> parent = nullptr;

	return task;
}

void ThreadPool::AddAsChild (Task * parent, Task * child)
{
	if (parent && child)
	{
		child -> parent = parent;
		++(parent -> pending);
	}
}

void ThreadPool::AddAsContinuation (Task * parent, Task * continuation)
{
	if (parent && continuation)
	{
		if (parent -> continuationCount < Task::MAX_CONTINUATIONS)
		{
			parent -> continuations[parent -> continuationCount] = continuation;
			++(parent -> continuationCount);
		}
	}
}

void ThreadPool::Enqueue (Task * task)
{
	if (task)
	{
		queue.Push(task);

		for (uint32 i = 0; i < workerThreadCount; ++i)
		{
			WorkerThread & thread = workerThreads[i];
			thread.Wakeup();
		}
	}
}

void ThreadPool::WaitAll ()
{
	while (queue.HasPending())
	{
		Task * task = queue.Pop();

		if (task) RunTask(task);
	}
}

void ThreadPool::WaitOne (Task * pendingTask)
{
	while (pendingTask -> pending > 0)
	{
		Task * task = queue.Pop();

		if (task) RunTask(task);
	}
}
