#include <Renderer/Utils/Window.h>

#include <iostream>
#include <thread>

int main () {

	Window window(800, 600, "Raptor");
	
	while (!window.shouldClose())
	{
		window.Update();
	}

	return 0;

}