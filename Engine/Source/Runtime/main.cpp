#include <Core/Common/Required.h>
#include <Core/Memory/GlobalStore.h>
#include <Renderer/Utils/Window.h>

int16 main (int16 argc, cchar argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Memory::GlobalStore;
	
	GlobalStore globalMemory(2048);
	
	void * buffer = globalMemory.Alloc(sizeof(WindowController), 0);
	
	WindowController * window = new (buffer) WindowController(640, 480, "Placeholder Window");
	
	while (!window -> ShouldClose())
	{
		window -> Update();
	}
	
	window -> Destroy();
	
	globalMemory.Reset();
	
	return 0;
}