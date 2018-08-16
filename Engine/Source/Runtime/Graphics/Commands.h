#pragma once

#include "RenderResource.h"

namespace Graphics::Commands
{

struct DrawIndexed
{
	unsigned int vertexArray;
	unsigned int indexCount;
};

enum CommandType
{
	DRAW_INDEXED
};

union CommandData
{
	DrawIndexed drawIndexed;
};

struct CommandPackage
{
	CommandType type;
	CommandData data;

	unsigned int sortKey;
};

}
