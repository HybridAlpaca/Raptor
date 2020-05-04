#pragma once

#include <Common/Required.h>

namespace Kernel
{
	class SharedLib
	{
		uint64 handle = 0;

		bool loaded = false;

	public:

		SharedLib (cchar path);
		SharedLib (const SharedLib & lvalue) = delete;
		SharedLib (SharedLib && rvalue);
		~SharedLib ();

		SharedLib & operator= (const SharedLib & rhs) = delete;
		SharedLib & operator= (SharedLib && rhs);

		void * ProcAddress (cchar symbol);
	};
}
