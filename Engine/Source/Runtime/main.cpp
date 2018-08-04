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
	
	Shader shader("/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.vs", "/home/cellman123/Desktop/Raptor/Engine/Assets/Shaders/Phong.fs");
	
	ModelLoader loader("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/");
	std::vector<Mesh> nanosuit = loader.Load("nanosuit/nanosuit.obj");
	
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	
	Renderer renderer;
	
	unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 640, 480); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << "\n";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
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
