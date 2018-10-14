#pragma once

#include <Common/Required.h>

namespace Graphics
{
	using CmdDispatch = void (void *);

	struct ClearCmd
	{
		static CmdDispatch * dispatch;

		float32 r;
		float32 g;
		float32 b;
		float32 a;
	};
}
