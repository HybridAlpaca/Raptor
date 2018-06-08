#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Core::Backend
{

/*
 *
 * name: DisplayConfig
 * @depends glfw3
 *
 * Stores basic configuration data that tells
 * a Display how to configure its internal GLfw
 * window.
 *
 */

struct DisplayConfig
{
	cchar title = "[ display::title ]";
	uint32 width = 640;
	uint32 height = 480;
};

/*
 *
 * name: Display
 *
 * @depends GLFW
 *
 * Acts as a wrapper class around a GLFW window.
 *
 */

class Display
{

	GLFWwindow * window = nullptr;

	bool running = true;

	void ProcessInput ();

public:

	Display (const DisplayConfig & config);
	Display (const Display & copy) = delete;
	~Display ();

	Display & operator= (const Display & rhs) = delete;

	void Clear (float r, float g, float b, float a);
	void BindContext ();
	void Update ();

	inline const bool Running () const { return running; }
};

}
