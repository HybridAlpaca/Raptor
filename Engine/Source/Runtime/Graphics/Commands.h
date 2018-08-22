#pragma once

#include "RenderResource.h"

namespace Graphics::Commands
{

struct Clear
{
	float r;
	float g;
	float b;
	float a;
};

struct DrawIndexed
{
	unsigned int vertexArray;
	unsigned int indexCount;
};

enum CommandType : unsigned int
{
	NOP,
	CLEAR,
	DRAW_INDEXED
};

union CommandData
{
	Clear clear;
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
