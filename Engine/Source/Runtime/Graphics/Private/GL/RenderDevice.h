#pragma once

#include "RenderState.h"
#include <Core/Common/Required.h>
#include <GL/glew.h>

namespace Graphics::GL
{

	class RenderDevice
	{
		RenderState state;

	public:

		RenderDevice ();

		/// Non-copyable
		RenderDevice (const RenderDevice & copy) = delete;

		~RenderDevice ();

		/// Non-copyable
		RenderDevice & operator= (const RenderDevice & rhs) = delete;

		void Init ();
	};

}
