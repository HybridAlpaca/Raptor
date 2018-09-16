#pragma once

#include <Raptor/Required.h>

namespace Core
{
	static const uint16 MAX_PLUGINS = 65535;

	struct SharedLibrary
	{
		using Handle = void *;

		Handle handle {};

		void Open (cchar path);
		void Close ();

		void * ProcAddress (cchar symbol);
	};
}
