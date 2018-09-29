#pragma once

class GLFWwindow;

namespace IO
{
	class Window
	{
		GLFWwindow * window = nullptr;

	public:

		Window ();
		~Window ();

		void PollEvents ();

		void SwapBuffers ();

		bool ShouldClose () const;
	};
}
