#pragma once

#include "Required.h"

namespace Raptor
{
	void Print (cchar string);
	void Println (cchar string);
	void Println (uint32 val);

	uintptr Strlen (cchar string);

	cchar ItoA (uint32 value, char * str);
}
