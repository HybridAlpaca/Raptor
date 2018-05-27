#include <Core/Common/Required.h>
#include <Core/Memory/BlobLoader.h>
#include <Renderer/Utils/Window.h>

int16 main (int16 argc, cchar argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Memory::BlobLoader;
	using Core::Memory::OptimizePolicy;
	
	BlobLoader allocator(2048, OptimizePolicy::BEST);
	
	void * buffer = allocator.Alloc(sizeof(WindowController), 8);
	
	WindowController * window = new (buffer) WindowController(640, 480, "Placeholder Window");
	
	while (!window -> ShouldClose())
	{
		window -> Update();
	}
	
	window -> Destroy();
	
	allocator.Free(buffer);
	
	return 0;
}