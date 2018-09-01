#pragma once

#include <Core/Common/Required.h>
#include <Constants.h>
#include <RenderStats.h>

namespace Graphics { class Display; }

/**
 *
 * @namespace Graphics::Backend
 * @author Seth Traman
 *
 **/

namespace Graphics::Backend
{

	// Device Operations

	/// @brief Initializes the render device for drawing
	void Initialize ();

	/// @brief Returns info about the internal state of the render device.  Useful for debugging and profiling
	FrameStats CurrentFrameStats ();

	// Resource Operations

	/// @brief Creates a shader program object with a vertex shader and a fragment shader
	/// @todo Create a more customizable shader pipeline with geometry & tess shaders
	ResourceHandle AllocateShaderProgram (cchar vertexCode, cchar fragmentCode);

	/// @brief Destroys a shader program object
	void DestroyShaderProgram (ResourceHandle resource);

	/// @brief Creates a vertex array object for storing vertices to be uploaded to the GPU
	ResourceHandle AllocateVertexArray (const VertexArrayDescription & desc);

	/// @brief Destroys a vertex array object
	void DestroyVertexArray (ResourceHandle resource);

	// Drawing Operations

	/// @brief Clears the framebuffer
	/// @todo Allow DSA-esque framebuffer specification
	void Clear (float r, float g, float b, float a);

	/// @brief Draws the specified vertex array with a given shader program
	/// @note Since this command is non-indexed, the index buffer is not used
	void Draw (ResourceHandle shader, ResourceHandle vertexArray, uint32 indexCount);

	// Windowing Utilities

	/// @brief Pushes the last rendered frame onto a display instance
	void Present (const Display & display);

	/// @brief Resize the internal renderer resolution
	void Resize (uint32 width, uint32 height);

}
