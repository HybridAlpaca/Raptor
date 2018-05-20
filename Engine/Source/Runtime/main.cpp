#include <Core/Common/Required.h>
#include <Core/Utils/ClassUtils.h>
#include <Renderer/Utils/Window.h>
#include <Core/Memory/AssetManager.h>

int16 main (int16 argc, cchar argv[])
{
	using Renderer::Utils::WindowController;
	using Core::Utils::TypeID;
	
	DEBUG(TypeID::value<uint16>());
	
	WindowController window(640, 480, "Placeholder Window");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
	
	return 0;
}