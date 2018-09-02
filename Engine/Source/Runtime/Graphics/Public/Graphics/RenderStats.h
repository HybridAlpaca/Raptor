#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	struct RenderStats
	{
		// Per-frame statistics

		uint32 drawCalls; ///< Number of API calls that resulted in a visual effect
		uint32 resourceCalls; ///< Number of API calls that related to resource management
		uint32 APICallErrors = 0; ///< Number of errors that occurred due to graphics API calls

		uint32 drawCacheAccesses = 0; ///< Number of lookups into render state cache
		uint32 drawCacheMisses = 0; ///< Number of times render state cache needed to be written to

		// Device internal statistics

		uint32 width; ///< Internal width of the backbuffer
		uint32 height; ///< Internal height of the backbuffer
	};
}
