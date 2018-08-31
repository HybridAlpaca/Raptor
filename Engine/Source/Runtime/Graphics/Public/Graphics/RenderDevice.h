#pragma once

#include <Core/Common/Required.h>

namespace Graphics { class Display; }

namespace Graphics::Backend
{

	// Device Operations

	void Init ();

	// Resource Operations

	/// Creates a shader program object with a vertex shader and a fragment shader
	/// @todo Create a more customizable shader pipeline with geometry & tess shaders
	uint32 AllocateShaderProgram (cchar vertexCode, cchar fragmentCode);

	void DestroyShaderProgram (uint32 program);

	// Drawing Operations

	/// Clears the framebuffer
	/// @todo Allow DSA-esque framebuffer specification
	void Clear (float r, float g, float b, float a);

	// Windowing Utilities

	/// Pushes the last rendered frame onto a display instance
	void Present (const Display & display);

	/// Resize the internal renderer resolution
	void Resize (uint32 width, uint32 height);

}
