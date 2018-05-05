#include <Core/Async/Scheduler.h>
#include <Renderer/Utils/Window.h>

#include <iostream>
#include <string>
#include <thread>

int main (int argc, char * argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Async::Scheduler;
	
	// Allocate 16 threads in thread pool
	Scheduler scheduler(15);
	
	scheduler.Schedule([] (void * data, std::string thread_id)
	{
		std::cout << "Hello from thread " << thread_id << "!" << "\n";
	});
	
	WindowController window(640, 480, "[ dummy display ]");
	
	glClearColor(1.0f, 0.0f, 0.6f, 1.0f);
	
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		window.Update();
	}
	
	scheduler.WaitAll();
	
}