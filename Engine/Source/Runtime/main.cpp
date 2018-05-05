#include <Core/Async/Scheduler.h>
#include <Renderer/Utils/Window.h>

#include <thread>
#include <iostream>
 
int main (int argc, char * argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Async::Scheduler;
	
	// 4 cores, subtract one for main thread
	Scheduler scheduler(3);
	
	scheduler.Schedule([] (void * data) ->
	void {
		std::cout << "Hello from thread " << std::this_thread::get_id() << "!" << "\n";
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