#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Graphics
{

	struct DisplayParams
	{
		cchar title = "";

		uint32 width = 800;
		uint32 height = 600;

		// OpenGL specific
		uint8 glVersionMajor = 3;
		uint8 glVersionMinor = 3;

		uint32 vsync = 1;
	};

	class Display
	{
		GLFWwindow * window;

	public:

		Display (const DisplayParams & params);
		Display (const Display & copy) = delete;
		~Display ();

		Display & operator= (const Display & rhs) = delete;

		bool Closed () const;
		void PollEvents () const;
		void SwapBuffers () const;

		uint32 FrameWidth () const;
		uint32 FrameHeight () const;
	};

}
