#pragma once

#include <Common/Required.h>

class GLFWwindow {};

namespace Graphics
{
	struct WindowDescriptor
	{
		cchar title   = "Hello, World!";

		uint32 width  = 800;
		uint32 height = 600;
	};

	class Window
	{
		GLFWwindow * window;

	public:

		Window (const WindowDescriptor & desc);
		Window (const Window & lvalue) = delete;
		Window (Window && rvalue);
		~Window ();

		Window & operator= (const Window & lvalue) = delete;
		Window & operator= (Window && rvalue);

		void BindContext () const;

		void PollEvents () const;

		void SwapBuffers () const;

		bool ShouldClose () const;
	};
}
