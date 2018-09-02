#pragma once

#include <Constants.h>
#include <Core/Common/Required.h>

namespace Graphics::Commands
{
	struct Clear
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct Draw
	{
		ResourceHandle vertexArray;
		ResourceHandle shaderProgram;

		uint32 indexCount;
	};

	union DrawCommand
	{
		Clear clear;
		Draw draw;
		Draw drawIndexed;
	};
}
