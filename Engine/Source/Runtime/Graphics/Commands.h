#pragma once

#include "RenderResource.h"

namespace Graphics::Commands
{

namespace Draw
{

struct Clear
{
	float r; ///< Normalized red value
	float g; ///< Normalized green value
	float b; ///< Normalized blue value
	float a; ///< Normalized alpha value
};

struct DrawIndexed
{
	unsigned int indexCount;
};

enum CommandType : unsigned int
{
	CLEAR,
	DRAW_INDEXED,
	NOP
};

union CommandData
{
	Clear clear;
	DrawIndexed drawIndexed;
};

}

struct DrawPackage
{
	Draw::CommandType type = Draw::CommandType::NOP;
	Draw::CommandData data;

	unsigned int resourceSlot = 0;
	unsigned int sortKey = 0;
};

}
