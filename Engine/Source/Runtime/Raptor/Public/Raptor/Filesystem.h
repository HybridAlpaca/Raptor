#pragma once

#include "Required.h"

#include <fstream>

namespace Raptor
{
	char * ReadFile (cchar path)
	{
		std::ifstream t(path);
		t.seekg(0, std::ios::end);

		uintptr size = t.tellg();

		char * buffer = new char [size + 1];

		t.seekg(0);
		t.read(buffer, size);
		buffer[size] = '\0';

		return buffer;
	}

	void DestroyFileData (cchar data)
	{
		delete [] data;
	}
}
