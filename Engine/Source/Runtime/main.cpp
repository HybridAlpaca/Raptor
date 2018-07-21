#include <Core/Shader.h>
#include <Core/Mesh.h>
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
		std::cerr << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
  glewInit();
  
  glViewport(0, 0, 640, 480);
  glfwSetFramebufferSizeCallback(window, FBSizeCallback);
	
	glClearColor(0.4f, 0.2f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Texture.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Texture.fs");
	
	std::vector<Vertex> vertices;
	Vertex v0;
	v0.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v0.texcoords = glm::vec2(1.0f, 1.0f);
	Vertex v1;
	v1.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v1.texcoords = glm::vec2(1.0f, 0.0f);
	Vertex v2;
	v2.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v2.texcoords = glm::vec2(0.0f, 0.0f);
	Vertex v3;
	v3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v3.texcoords = glm::vec2(0.0f, 0.1f);
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };
	
	unsigned int texture;
	glGenTextures(1, & texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load("/home/cellman123/Desktop/Raptor/Engine/Assets/Icons/raptor-logo.png", &  width, & height, & nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << "\n";
	}
	stbi_image_free(data);
	
	std::vector<Texture> textures;
	Texture t0;
	t0.id = texture;
	t0.type = TextureType::DIFFUSE;
	textures.push_back(t0);
	
	Mesh mesh(vertices, indices, textures);
	
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window, camera);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model(1.0f);
		glm::mat4 projection(1.0f);
		// model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
		
		shader.Bind();
		shader.Mat4("model", model);
		shader.Mat4("view", camera.ViewMatrix());
		shader.Mat4("projection", projection);

		mesh.Draw(shader);
		
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glfwTerminate();
	
	return 0;
}
