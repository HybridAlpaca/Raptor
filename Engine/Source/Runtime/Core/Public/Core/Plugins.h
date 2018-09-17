#pragma once

#include <Raptor/Required.h>

namespace Core
{
	struct SharedLibrary
	{
		using Handle = void *;

		Handle handle {};

		void Open (cchar path);
		void Close ();

		void * ProcAddress (cchar symbol);
	};
}
