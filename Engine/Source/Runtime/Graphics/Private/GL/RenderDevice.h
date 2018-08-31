#pragma once

#include <Constants.h>
#include <Core/Common/Required.h>

namespace Graphics { class Display; }

namespace Graphics::Backend
{

	// Drawing Functions

	void Clear (float r, float g, float b, float a);

	// Windowing Utilities

	void Present (const Display & display);

	void Resize (uint32 width, uint32 height);

}
