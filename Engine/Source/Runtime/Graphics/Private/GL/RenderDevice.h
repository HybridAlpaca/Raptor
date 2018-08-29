#pragma once

#include "RenderState.h"

#include <Display.h>
#include <RenderResource.h>
#include <Core/Common/Required.h>

namespace Graphics::GL
{

	class RenderDevice
	{
		RenderState state;

	public:

		RenderDevice (const Display & display);

		/// Non-copyable
		RenderDevice (const RenderDevice & copy) = delete;

		~RenderDevice ();

		/// Non-copyable
		RenderDevice & operator= (const RenderDevice & rhs) = delete;

		void Clear (float r, float g, float b, float a);
	};

}
