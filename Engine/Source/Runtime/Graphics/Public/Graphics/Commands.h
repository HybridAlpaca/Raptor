#pragma once

#include <RenderResource.h>
#include <Core/Common/Required.h>

#define DECLARE_DISPATCH_FUNC(cmd) \
	using DispatchFunc = void (*) (const cmd &); \
	static DispatchFunc Dispatch;

namespace Graphics::Commands
{

	/**
	 * @todo Factor Clear into part of the render state that happens before all draw calls in the layer
	 **/
	struct Clear
	{
		DECLARE_DISPATCH_FUNC(Clear);

		float r; ///< Red value of color buffer
		float g; ///< Green value of color buffer
		float b; ///< Blue value of color buffer
		float a; ///< Alpha value of color buffer
	};

	struct Draw
	{
		DECLARE_DISPATCH_FUNC(Draw);

		ResourceHandle shaderProgram; ///< The shader program to draw with
		ResourceHandle vertexArray; ///< The vertex array to draw

		uint32 indexCount; ///< Number of vertices / indices to draw
		uint32 indexOffset; ///< Offset of first vertex / index  to be drawn
	};

	struct DrawIndexed
	{
		DECLARE_DISPATCH_FUNC(DrawIndexed);

		ResourceHandle shaderProgram; ///< The shader program to draw with
		ResourceHandle vertexArray; ///< The vertex array to draw

		uint32 indexCount; ///< Number of indices to draw
		uint32 indexOffset; ///< Offset of first index to be drawn
	};
}
