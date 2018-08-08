#pragma once

#include <glm/glm.hpp>

namespace Graphics
{

/**
 *
 * @namespace Commands
 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
 * @author Seth Traman
 * @date Aug 2018
 *
 **/

namespace Commands
{

	/**
	 *
	 * @enum Commands::Type
	 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
	 * @author Seth Traman
	 * @date Aug 2018
	 *
	 * @brief An enumeration for all possible command types
	 * @todo Support more command types
	 *
	 **/

	enum Type : unsigned int
	{
		CLEAR,
		DRAW,
		DRAW_INDEXED,

		BIND_SHADER_PROGRAM
	};

	/**
	 *
	 * @union Data
	 * @headerfile CommandBuffer.h <Graphics/CommandBuffer.h>
	 * @author Seth Traman
	 * @date Aug 2018
	 *
	 * @brief Intended for storing command information fields for every type of supported command
	 * @todo Support more types of command data
	 *
	 */

	union Data
	{
		const char * name;
	};

	struct Clear
	{
		glm::vec4 color;
		unsigned int flags;
	};

	struct Draw
	{
		unsigned int indexCount;
		unsigned int startIndex;
		unsigned int primitiveType;
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
 * @public command : The type of the command
 * @public data : Any data requireds for the execution of the command
 * @public resourceSlot : the ID of the resource being accessed, if any.  In OpenGL, this could be the ID of a texture, shader, VAO, or any such stateful object.
 *
 **/

struct DeferredCommand
{
	Commands::Type command;
	Commands::Data data;

	unsigned int resourceSlot;
};

}
