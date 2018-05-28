#include <Core/Common/Required.h>
#include <Core/Memory/GlobalStore.h>
#include <Renderer/Utils/Window.h>

/*

GlobalStore globalMemory(Core::Memory::Gigabytes(2));

HeapStore heap(globalMemory, Core::Memory::Megabytes(512));

Foo * theFoo = new Foo(bar, & theBaz);

*/

int16 main (int16 argc, cchar argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Memory::GlobalStore;
	
	GlobalStore globalMemory(8192);
	
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