#pragma once

#include <Core/Common/Required.h>
#include <Constants.h>

namespace Graphics { class Display; }

namespace Graphics::Backend
{

	// Device Operations

	void Init ();

	// Resource Operations

	/// Creates a shader program object with a vertex shader and a fragment shader
	/// @todo Create a more customizable shader pipeline with geometry & tess shaders
	ResourceHandle AllocateShaderProgram (cchar vertexCode, cchar fragmentCode);

	/// Destroys a shader program object
	void DestroyShaderProgram (ResourceHandle resource);

	ResourceHandle AllocateVertexArray (float * vertices);

	void DestroyVertexArray (ResourceHandle resource);

	// Drawing Operations

	/// Clears the framebuffer
	/// @todo Allow DSA-esque framebuffer specification
	void Clear (float r, float g, float b, float a);

	void Draw (ResourceHandle shader, ResourceHandle vertexArray, uint32 indexCount);

	// Windowing Utilities

	/// Pushes the last rendered frame onto a display instance
	void Present (const Display & display);

	/// Resize the internal renderer resolution
	void Resize (uint32 width, uint32 height);

}
