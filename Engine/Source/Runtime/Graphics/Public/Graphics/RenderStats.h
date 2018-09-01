#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	struct FrameStats
	{
		uint32 APICallCount = 0;
		uint32 APICallErrors = 0;

		uint32 drawCacheAccesses = 0;
		uint32 drawCacheMisses = 0;

		inline void Reset ()
		{
			APICallCount = 0;
			APICallErrors = 0;
			drawCacheAccesses = 0;
			drawCacheMisses = 0;
		}

		inline uint32 CalcDrawCacheHits () const
		{
			return drawCacheAccesses - drawCacheMisses;
		}
	};
}
