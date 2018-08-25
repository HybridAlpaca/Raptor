#pragma once

#include "DeviceState.h"
#include "../DrawContext.h"

namespace Graphics::Backend::GL
{

class RenderDevice
{
	DeviceState state;

public:

	RenderDevice ();
	~RenderDevice ();

	void Dispatch (const DrawContext & ctx);
};

}
