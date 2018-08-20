#pragma once

#include "RenderResource.h"

namespace Graphics::Commands
{

struct CreateVertexArray
{
	// the thing goes here
};

struct DrawIndexed
{
	unsigned int vertexArray;
	unsigned int indexCount;
};

enum CommandType
{
	NOP,
	DRAW_INDEXED
};

union CommandData
{
	CreateVertexArray vertexArray;
	DrawIndexed drawIndexed;
};

struct CommandPackage
{
	CommandType type = CommandType::NOP;
	CommandData data;

	unsigned int resourceSlot = 0;
	unsigned int sortKey = 0;
};

}
