#pragma once

#include "Semaphore.h"

#include <thread>

namespace Kernel
{
	struct WorkerThread
	{
		Semaphore	wakeup;
		Semaphore	done;

		std::thread thread;

		void Shutdown ()
		{
			Wakeup();
			thread.join();
		}

		void Wakeup ()
		{
			wakeup.Notify();
		}
	};
}
