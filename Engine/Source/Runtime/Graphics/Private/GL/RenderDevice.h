#pragma once

namespace Graphics::GL
{

	class RenderDevice
	{

	public:

		RenderDevice ();
		RenderDevice (const RenderDevice & copy) = delete;
		~RenderDevice ();

		RenderDevice & operator= (const RenderDevice & rhs) = delete;
	};

}
