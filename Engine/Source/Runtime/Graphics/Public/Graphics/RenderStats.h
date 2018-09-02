#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	struct RenderStats
	{
		// Per-frame statistics

		uint32 APICallCount = 0; ///< Number of graphics API calls that took place
		uint32 APICallErrors = 0; ///< Number of errors that occurred due to graphics API calls

		uint32 drawCacheAccesses = 0; ///< Number of lookups into render state cache
		uint32 drawCacheMisses = 0; ///< Number of times render state cache needed to be written to

		// Resource statistics

		uint32 vertexArrayCount = 0;
		uint32 shaderProgramCount = 0;

		// Device internal statistics

		uint32 width; ///< Internal width of the backbuffer
		uint32 height; ///< Internal height of the backbuffer
	};
}
