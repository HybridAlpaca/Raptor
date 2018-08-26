#pragma once

#include "RenderResource.h"
#include <Core/Common/Required.h>

namespace Graphics
{

namespace Commands
{

/*
 *
 * Draw comands & data structures
 *
 */

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

enum DrawCommandType : uint8
{
	CLEAR,
	DRAW_INDEXED
};

union DrawCommandData
{
	Clear clear;
	DrawIndexed drawIndexed;
};

/*
 *
 * Resource commands and data structures
 *
 */

enum ResourceCommandType : uint8
{
	VERTEX_ARRAY,
	TEXTURE_2D,
	SHADER
};

}

struct DrawPacket
{
	Commands::DrawCommandType type;
	Commands::DrawCommandData data;

	// On second thought, is a resource slot even necessary?
	uint32 resourceSlot = 0;

	uint32 sortKey = 0;
};

}
