#pragma once

#include <Raptor/Required.h>

namespace Graphics::Display
{
	using Handle = uint16;

	struct WindowDescriptor
	{
		cchar title;

		uint32 width;
		uint32 height;
	};

	class Window
	{
		Handle handle;

	public:

		Window (const WindowDescriptor & desc);
		Window (const Window & copy) = delete;
		~Window ();

		Window & operator= (const Window & rhs) = delete;

		float64 CurrentTime () const;

		void PollEvents () const;
		void SwapBuffers () const;

		uint32 FrameWidth () const;
		uint32 FrameHeight () const;

		bool ShouldClose () const;
		void ShouldClose (bool value) const;
	};
}
