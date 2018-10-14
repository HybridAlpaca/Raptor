#pragma once

#include "WorkQueue.h"

namespace Kernel
{
	class WorkerThread;

	class ThreadPool
	{
		WorkQueue      queue;
		WorkerThread * workerThreads;

		bool shutdown;

		uint32 workerThreadCount;
		uint32 logicalThreadCount;

		void InitializeWorkers ();

		void Worker (uint32 index);

		void RunTask (Task * task);

		void WaitForChildren (Task * task);

	public:

		ThreadPool ();

		ThreadPool (uint32 workers);

		~ThreadPool ();

		Task * Allocate ();

		void AddAsChild (Task * parent, Task * child);

		void AddAsContinuation (Task * parent, Task * continuation);

		void Enqueue (Task * task);

		void WaitAll ();

		void WaitOne (Task * pendingTask);

		inline uint32 LogicalThreadCount () const { return logicalThreadCount; }

		inline uint32 WorkerThreadCount () const { return workerThreadCount; }
	};
}
