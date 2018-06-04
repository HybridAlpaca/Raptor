#include <Core/Common/Required.h>
#include <Graphics/Utils/Window.h>
#include <Graphics/Utils/Shader.h>
#include <Graphics/Renderer/Primitive.h>

int16 main (int16 argc, cchar argv[])
{
	using namespace Graphics::Utils;
	using namespace Graphics::Renderer;
	
	WindowController window(640, 480, "Placeholder Window");
	Primitive priRenderer;
	Shader basicShader(
		"/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.vs",
		"/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.fs"
	);
	
	while (!window.ShouldClose())
	{
		window.Update();
		priRenderer.Preprocess();
	}
	
	return 0;
}