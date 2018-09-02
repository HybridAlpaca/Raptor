#pragma once

#include <Constants.h>
#include <Core/Common/Required.h>

#define DECLARE_DISPATCH_FUNC(cmd) \
	using DispatchFunc = void (*) (const cmd &); \
	static DispatchFunc Dispatch;

namespace Graphics::Commands
{

	/**
	 * @todo Factor Clear into part of the render state that happens before all other draw calls
	 **/
	struct Clear
	{
		DECLARE_DISPATCH_FUNC(Clear);

		float r;
		float g;
		float b;
		float a;
	};

	struct Draw
	{
		DECLARE_DISPATCH_FUNC(Draw);

		ResourceHandle shaderProgram;
		ResourceHandle vertexArray;

		uint32 indexCount;
	};

	struct DrawIndexed
	{
		DECLARE_DISPATCH_FUNC(DrawIndexed);

		ResourceHandle shaderProgram;
		ResourceHandle vertexArray;

		uint32 indexCount;
		uint32 indexOffset;
	};
}
