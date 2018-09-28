#include "Kernel.h"

#include <IO/Window.h>

#include <iostream>

using namespace Core;

void Kernel::Create ()
{
	std::cout << "[C++] Create Kernel" << '\n';
}

int Kernel::Destroy ()
{
	std::cout << "[C++] Destroy Kernel" << '\n';

	return 0;
}
