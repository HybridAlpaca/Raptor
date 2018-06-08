#pragma once

#include <Core/Common/Required.h>

namespace Core::Backend
{

/*
 *
 * name: InputHandler
 * @depends SDL2
 *
 * Keeps track of inputs from the OS via SDL
 * and operates on them directly.
 *
 * TODO: Tie this to a global event system
 *
 */

class InputHandler
{
public:

	void Process (Application & app);
};

}
