#pragma once

#include <Common/Required.h>

#include <atomic>

namespace Kernel
{
	/// A function representing a single unit of work to be done in the task system
	using WorkItem = void (void *);

	/**
	 * @struct Task
	 * @author Seth Traman
	 *
	 * @brief An object representing the smallest unit of work in the Raptor task system
	 *
	 **/

	struct Task
	{
		static constexpr const uint32 DATA_SIZE_BYTES   = 64;  ///< Max auxillary data per task
		static constexpr const uint32 MAX_CONTINUATIONS = 32;  ///< Max dependants per task
		static constexpr const uint32 MAX_TASKS         = 256; ///< Max active tasks per given timeframe

		/// A function pointer to the unit of work to be executed
		WorkItem * function;

		/// Any auxillary data the WorkItem needs to run
		char data [DATA_SIZE_BYTES];

		/// This task's parent, used for grouping similar tasks
		Task * parent;

		/// This child's continuations, used for specifying dependancies
		Task * continuations [MAX_CONTINUATIONS];

		/// The number of pending children this task has remaining
		std::atomic<uint16> pending;

		/// The number of continuations / dependants this task has
		std::atomic<uint16> continuationCount;
	};

	template <typename T>
	inline constexpr T * TaskData (Task * task)
	{
		return (T *)(& (task -> data[0]));
	}
}
