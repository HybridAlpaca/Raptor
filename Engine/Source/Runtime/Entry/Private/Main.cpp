#include <Kernel/Kernel.h>
#include <IO/Window.h>

#include <iostream>

int main (int argc, char ** argv)
{
	Core::Kernel kernel(std::thread::hardware_concurrency() - 1);

	IO::Window window;

	while (!window.ShouldClose())
	{
		window.PollEvents();
		window.SwapBuffers();
	}

	kernel.Wait();

	return 0;
}
