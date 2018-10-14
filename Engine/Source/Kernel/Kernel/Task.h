#pragma once

#include <Common/Required.h>

#include <atomic>

namespace Kernel
{
	using WorkItem = void (void *);

	struct Task
	{
		static const uint32 DATA_SIZE_BYTES   = 64;
		static const uint32 MAX_CONTINUATIONS = 32;
		static const uint32 MAX_TASKS         = 256;

		WorkItem * function;
		char data [DATA_SIZE_BYTES];

		Task * parent;
		Task * continuations [MAX_CONTINUATIONS];

		std::atomic<uint16> pending;
		std::atomic<uint16> continuationCount;
	};

	template <typename T>
	inline T * TaskData (Task * task)
	{
		return (T *)(& (task -> data[0]));
	}
}
