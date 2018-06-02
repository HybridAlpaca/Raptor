#include <Core/Common/Required.h>
#include <Core/Memory/HeapAlloc.h>
#include <Core/Memory/Utils.h>
#include <Renderer/Utils/Window.h>

#include <cstdlib>

int16 main (int16 argc, cchar argv[])
{
	using namespace Renderer::Utils;
	using namespace Core::Memory;
	
	HeapAllocator heap(Megabytes(16), OptimizePolicy::BEST);
	
	WindowController window(640, 480, "Placeholder Window");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
	
	window.Destroy();
	
	return 0;
}