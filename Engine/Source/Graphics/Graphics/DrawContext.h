#pragma once

namespace Graphics
{
	class DrawContext
	{

	public:

		DrawContext ();
		~DrawContext ();

		/// Execute the recorded draw calls on the GPU
		/// @note Externally synchronized
		void Dispatch ();
	};
}
