#include <Core/Shader.h>
#include <Core/Model.h>
#include <Core/Camera.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "STBI/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

void FBSizeCallback (GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow * window = glfwCreateWindow(640, 480, "Lorum Ipsum", nullptr, nullptr);
	if (!window)
	{
		//
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
		//
		glfwTerminate();
		return 1;
	}
  
  glViewport(0, 0, 640, 480);
  glfwSetFramebufferSizeCallback(window, FBSizeCallback);
	
	glClearColor(0.4f, 0.2f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.fs");
	
	Model stuff("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/nanosuit/nanosuit.obj");
	
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window, camera);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model(1.0f);
		glm::mat4 projection(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
		
		shader.Bind();
		shader.Mat4("model", model);
		shader.Mat4("view", camera.ViewMatrix());
		shader.Mat4("projection", projection);
		
		shader.Vec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.Vec3("lightPos", camera.Position());
		shader.Vec3("viewPos", camera.Position());

		stuff.Draw(shader);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}
