#pragma once

#include "PluginsApi.h"
#include "RenderDevice.h"

namespace Graphics::Api
{
	class v0 : public GraphicsApi
	{
		virtual void Clear (float32 color [4]) override
		{
			RenderDevice::Clear(color);
		}
	};
}
