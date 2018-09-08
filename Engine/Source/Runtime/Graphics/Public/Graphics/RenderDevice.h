#pragma once

#include <Raptor/Required.h>
#include <RenderResource.h>
#include <Commands.h>
#include <RenderStats.h>

namespace Graphics { class Display; }

/**
 *
 * @namespace Graphics::RenderDevice
 * @author Seth Traman
 *
 * @warning The render device is NOT thread safe, especially resource operations.  If you need to do any work with GPU resources, this work should be done on the rendering thread.
 *
 **/

namespace Graphics::RenderDevice
{
	// Data types

	/// Any of the possible graphics API's that the render device uses internally
	enum class GraphicsBackend
	{
		NONE,
		OPENGL_CORE,
		// OPENGL_ES,
		// WEBGL,
		// D3D11,
		// D3D12,
		// METAL,
		// VULKAN
	};

	struct InitDescriptor
	{
		bool debug = false;
	};

	// Device Operations

	/// Initializes the render device for drawing
	void Initialize (const InitDescriptor & desc);

	/// @return The backend API that the render device is using
	inline GraphicsBackend BackendType ();

	/// Returns info about the internal state of the render device.  Useful for debugging and profiling
	RenderStats Stats ();

	// Resource Operations

	/// Creates a shader program object with a vertex shader and a fragment shader
	/// @todo Create a more customizable shader pipeline with geometry & tess shaders
	RenderResource AllocateShaderProgram (cchar vertexCode, cchar fragmentCode);

	/// Destroys a shader program object
	void DestroyShaderProgram (RenderResource resource);

	/// Creates a vertex array object for storing vertices to be uploaded to the GPU
	RenderResource AllocateVertexArray ();

	/// Destroys a vertex array object
	void DestroyVertexArray (RenderResource & resource);

	RenderResource AllocateBuffer (RenderResource vertexArray, const void * data, const BufferDescriptor & desc);

	void DestroyBuffer (RenderResource & resource);

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
