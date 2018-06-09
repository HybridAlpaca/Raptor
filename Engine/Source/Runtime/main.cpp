#include <Core/Common/Required.h>
#include <Core/Backend/Display.h>
#include <Graphics/Utils/Shader.h>
#include <Graphics/Model/Geometry.h>

#include <GL/glew.h>

#include <vector>

/*
 *
 * name: main
 * @param int32 argc, cchar argv[]]
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
	using Graphics::Utils::Shader;
	using Graphics::Model::Geometry;
	using Graphics::Model::Vertex;

	DisplayConfig config;
	Display display(config);

	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Basic.fs");

	std::vector<Vertex> vertices =
	{
		Vertex( 0.5f, -0.5f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.0f),
		Vertex( 0.0f,  0.5f, 0.0f)
	};

	std::vector<uint32> indices =
	{
		0, 1, 2
	};

	Geometry geometry(vertices, indices);

	glClearColor(0.1f, 0.2f, 0.7f, 1.0f);

	glViewport(0, 0, 640, 480);

	while (display.Running())
	{
		if (display.GetKey(256) || display.GetKey(81))
		{
			display.Running(false);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		glBindVertexArray(geometry.vao);
		glDrawElements(GL_TRIANGLES, geometry.indexCount, GL_UNSIGNED_INT, 0);

		display.Update();
	}

	return 0;
}
