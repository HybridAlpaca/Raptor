#pragma once

#include <Common/Required.h>

namespace Graphics
{
	struct SwapChainDesc
	{
		uint32 width;
		uint32 height;

		cchar title;
	};
}

extern "C" void CreateSwapChain (const Graphics::SwapChainDesc & desc);
