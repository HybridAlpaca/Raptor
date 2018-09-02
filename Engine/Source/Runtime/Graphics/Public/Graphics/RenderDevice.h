#pragma once

#include <Core/Common/Required.h>
#include <RenderResource.h>
#include <Commands.h>
#include <RenderStats.h>

namespace Graphics { class Display; }

/**
 *
 * @namespace Graphics::Backend
 * @author Seth Traman
 *
 **/

namespace Graphics::RenderDevice
{

	// Device Operations

	/// Initializes the render device for drawing
	void Initialize ();

	/// Returns info about the internal state of the render device.  Useful for debugging and profiling
	RenderStats Stats ();

	// Resource Operations

	/// Creates a shader program object with a vertex shader and a fragment shader
	/// @todo Create a more customizable shader pipeline with geometry & tess shaders
	ResourceHandle AllocateShaderProgram (cchar vertexCode, cchar fragmentCode);

	/// Destroys a shader program object
	void DestroyShaderProgram (ResourceHandle resource);

	/// Creates a vertex array object for storing vertices to be uploaded to the GPU
	ResourceHandle AllocateVertexArray (const VertexArrayDescription & desc);

	/// Destroys a vertex array object
	void DestroyVertexArray (ResourceHandle resource);

	// Drawing Operations

	/// Clears the framebuffer
	/// @todo Allow DSA-esque framebuffer specification
	void Clear (const Commands::Clear & cmd);

	/// Draws the specified vertex array with a given shader program
	/// @note Since this command is non-indexed, the index buffer is not used.  See DrawIndexed for more
	void Draw (const Commands::Draw & cmd);

	/// Draws a vertex array by its indices with a provided shader program
	void DrawIndexed (const Commands::DrawIndexed & cmd);

	// Windowing Utilities

	/// Pushes the last rendered frame onto a display instance
	void Present (const Display & display);

	/// Resize the internal renderer resolution
	void Resize (uint32 width, uint32 height);

}
