#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	struct FrameStats
	{
		uint32 APICallCount = 0; ///< Number of graphics API calls that took place
		uint32 APICallErrors = 0; ///< Number of errors that occurred due to graphics API calls

		uint32 drawCacheAccesses = 0; ///< Number of lookups into render state cache
		uint32 drawCacheMisses = 0; ///< Number of times render state cache needed to be written to

		/// @brief Resets the frame stats to its initial state
		inline void Reset ()
		{
			APICallCount = 0;
			APICallErrors = 0;
			drawCacheAccesses = 0;
			drawCacheMisses = 0;
		}

		/// @brief Calculates render state cache hits
		/// @return Number of render state cache hits based on total cache lookups and cache misses
		inline uint32 CalcDrawCacheHits () const
		{
			return drawCacheAccesses - drawCacheMisses;
		}
	};
}
