#pragma once

#include <glm/glm.hpp>

namespace Graphics
{

/**
 *
 * @namespace Graphics::Commands
 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
 * @author Seth Traman
 * @date Aug 2018
 *
 * @brief Contains data required for DeferredCommand creation
 *
 **/

namespace Commands
{

	/**
	 *
	 * @enum Type
	 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
	 * @author Seth Traman
	 * @date Aug 2018
	 *
	 * @brief An enumeration for all possible command types
	 * @todo Support more command types
	 *
	 **/

	enum class Type
	{
		CLEAR,								///< Clears a given framebuffer
		DRAW,									///< Draws a VAO without index buffer
		DRAW_INDEXED,					///< Draws a VAO with index buffer

		BIND_SHADER_PROGRAM		///< Instructs graphics library to use selected shader program
	};

	/// Command information
	struct Clear
	{
		glm::vec4 color;		///< RGBA color buffer clear
		unsigned int flags; ///< Bitmask for whether to clear color, depth, stencil
	};

	/// Command information
	struct Draw
	{
		unsigned int indexCount;		///< Number of indices to be drawn
		unsigned int startIndex;		///< Starting index
		unsigned int primitiveType;	///< Triangles, quads, strips, lines, etc.
	};

	/**
	 *
	 * @union Data
	 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
	 * @author Seth Traman
	 * @date Aug 2018
	 *
	 * @brief Intended for storing command information fields for every supported command type
	 * @todo Support more types of command data
	 *
	 */

	union Data
	{
		Clear clear;
		Draw draw;
		unsigned int index;
		const char * name;
	};
}

/**
 *
 * @struct DeferredCommand
 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
 * @author Seth Traman
 * @date Aug 2018
 *
 * @brief Structure describing an individual graphics library command
 *
 **/

struct DeferredCommand
{
	Commands::Type command;			///< The type of command to be run
	Commands::Data data;				///< Data required for execution of command

	unsigned int resourceSlot;	///< Location or ID of resource to be used during execution
};

}
