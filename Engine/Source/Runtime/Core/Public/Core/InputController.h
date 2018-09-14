#pragma once

#include <Raptor/Required.h>

namespace Core::Abstract
{
	struct InputController
	{
		virtual void KeyDown () {}
		virtual void KeyUp () {}
	};
}
