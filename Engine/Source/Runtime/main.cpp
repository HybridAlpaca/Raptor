#include <Core/Shader.h>
#include <Core/Model.h>
#include <Core/Camera.h>
#include <Core/Renderer.h>
#include <Core/Display.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "STBI/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

void ProcessInput (GLFWwindow * window, Camera & camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::FORWARD, 0.16f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::BACKWARD, 0.16f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::LEFT, 0.16f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::RIGHT, 0.16f);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::UP, 0.16f);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraControl::DOWN, 0.16f);
}

int main (int argc, char ** argv)
{
	Display display;

	Renderer renderer;

	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.fs");

	ModelLoader loader("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/");
	std::vector<Mesh> nanosuit = loader.Load("nanosuit/nanosuit.obj");

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	while (!display.ShouldClose())
	{
		ProcessInput(display.Window(), camera);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		shader.Bind();
		shader.Mat4("model", model);
		shader.Mat4("view", camera.ViewMatrix());
		shader.Mat4("projection", projection);

		shader.Vec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.Vec3("lightPos", camera.Position());
		shader.Vec3("viewPos", camera.Position());

		for (unsigned int i = 0; i < nanosuit.size(); i++)
		{
			renderer.Render(nanosuit[i], shader);
		}

		display.Update();
	}

	return 0;
}
