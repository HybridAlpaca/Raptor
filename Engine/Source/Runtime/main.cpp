#include <Core/Common/Required.h>
#include <Core/Backend/Display.h>
#include <Graphics/Utils/Shader.h>
#include <Graphics/Model/Geometry.h>
#define STB_IMAGE_IMPLEMENTATION
#include <Graphics/Model/ModelLoader.h>
#include <Graphics/Utils/TextureLoader.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

/*
 *
 * name: main
 * @param int32 argc, cchar argv[]
 * @return int32
 *
 * @todo Separate platform-dependant implementations
 * I.E. One file with `main` for *nix OS's, and one
 * with `WinMain` for win32 and win64.  Then, create
 * a separate init file with an entry point specified
 * to the linker, which would include the appropriate
 * function at compile time.
 *
 */

int32 main (int32 argc, cchar argv[])
{
	using namespace Core::Backend;
	using namespace Graphics::Utils;
	using namespace Graphics::Model;

	DisplayConfig config;
	// change any config settings here

	Display display(config);

	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.fs");

	ModelLoader model("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/nanosuit/nanosuit.obj");

	glClearColor(0.1f, 0.2f, 0.7f, 1.0f);

	while (display.Running())
	{
		if (display.GetKey(256) || display.GetKey(81))
		{
			display.Running(false);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		model.Draw(shader);

		display.Update();
	}

	return 0;
}
