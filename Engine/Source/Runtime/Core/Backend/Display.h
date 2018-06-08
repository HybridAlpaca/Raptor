#pragma once

#include <Core/Common/Required.h>
#include "Application.h"

class GLFWwindow {};

namespace Core::Backend
{

/*
 * 
 * name: Display
 * 
 * @depends Core, GLFW
 * 
 */
class Display
{
	Core::Backend::Application & app;
	
	GLFWwindow * window = nullptr;
	
	void ProcessInput ();

public:

	Display (Core::Backend::Application & application);
	Display (const Display & copy) = delete;
	~Display ();

	Display & operator= (const Display & rhs) = delete;

	void Clear (float r, float g, float b, float a);
	void BindContext ();
	void Update ();
};

}
