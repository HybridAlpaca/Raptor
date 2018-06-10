#include <Core/Common/Required.h>
#include <Core/Backend/Display.h>
#include <Graphics/Utils/Shader.h>
#include <Graphics/Model/Geometry.h>
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

	uint32 src0 = LoadTexture("/home/cellman123/Desktop/Raptor/Engine/Assets/Icons/awesomeface.png");
	uint32 src1 = LoadTexture("/home/cellman123/Desktop/Raptor/Engine/Assets/Icons/container.jpg");

	Vertex vec0, vec1, vec2, vec3;

	vec0.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vec0.texCoord = glm::vec2(1.0f, 1.0f);

	vec1.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vec1.texCoord = glm::vec2(1.0f, 0.0f);

	vec2.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vec2.texCoord = glm::vec2(0.0f, 0.0f);

	vec3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vec3.texCoord = glm::vec2(0.0f, 1.0f);

	std::vector<Vertex> vertices = { vec0, vec1, vec2, vec3 };

	Texture tex0, tex1;

	tex0.id = src0;
	tex0.type = TextureType::DIFFUSE;
	tex0.path = "/home/cellman123/Desktop/Raptor/Engine/Assets/Icons/awesomeface.png";


	tex1.id = src1;
	tex1.type = TextureType::DIFFUSE;
	tex1.path = "/home/cellman123/Desktop/Raptor/Engine/Assets/Icons/container.jpg";

	std::vector<Texture> textures = { tex0, tex1 };

	std::vector<uint32> indices =  { 0, 1, 3, 1, 2, 3 };

	Mesh quad(vertices, indices, textures);

	glClearColor(0.1f, 0.2f, 0.7f, 1.0f);

	while (display.Running())
	{
		if (display.GetKey(256) || display.GetKey(81))
		{
			display.Running(false);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		quad.Draw(shader);

		display.Update();
	}

	FreeTexture(& src0);
	FreeTexture(& src1);

	return 0;
}
