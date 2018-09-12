#pragma once

#include <Raptor/Required.h>
#include <RenderResource.h>
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
		NONE,         /// Represents a null render device, useful for mockups & testing
		OPENGL_CORE,  /// Using an OpenGL 3.3+ Core profile backend
		// OPENGL_ES,
		// WEBGL,
		// D3D11,
		// D3D12,
		// METAL,
		// VULKAN,
		OTHER         /// Any backend other than those specified above, i.e. a user-defined render device
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

	/// Allocates a shader of the specified type
	RenderResource AllocateShader (cchar code, ShaderType type);

	/// Destroys a shader
	void DestroyShader (RenderResource & resource);

	/// Creates and links a shader program with specified shaders
	RenderResource AllocateShaderProgram (const RenderResource * const shaders, uint32 shaderCount);

	/// Destroys a shader program object
	void DestroyShaderProgram (RenderResource resource);

	/// Creates a vertex array object for storing vertices to be uploaded to the GPU
	RenderResource AllocateVertexArray ();

	/// Destroys a vertex array object
	void DestroyVertexArray (RenderResource & resource);

	/// Creates a segment of memory on the GPU for storing vertices, indices, or any generic data
	RenderResource AllocateBuffer (RenderResource vertexArray, const void * data, const BufferDescriptor & desc);

	/// Frees a segment of memory allocated as a GPU buffer
	void DestroyBuffer (RenderResource & resource);

	// Drawing Operations

	/// Clears the framebuffer
	/// @todo Allow DSA-esque framebuffer specification
	void Clear (float color [4]);

	void ShaderUniform (RenderResource program, cchar name, float32 value);
	void ShaderUniform (RenderResource program, cchar name, float32 values [3]);

	/// Draws the specified vertex array with a given shader program
	/// @note Since this command is non-indexed, the index buffer is not used.  See DrawIndexed for more
	void Draw (RenderResource program, RenderResource vertexArray, uint32 indexCount, uint32 indexOffset);

	/// Draws a vertex array by its indices with a provided shader program
	void DrawIndexed (RenderResource program, RenderResource vertexArray, uint32 indexCount, uint32 indexOffset);

	// Windowing Utilities

	/// Pushes the last rendered frame onto a display instance
	void Present (const Display & display);

	/// Resize the internal renderer resolution
	void Resize (uint32 width, uint32 height);

}
