#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Core::Backend
{

/*
 *
 * name: DisplayConfig
 *
 * Stores basic configuration data that tells
 * a Display how to configure its internal GLfw
 * window.
 *
 */

struct DisplayConfig
{
	// window hints
	cchar title	= "[ Lorem Ipsum ]";
	uint32 width = 640;
	uint32 height = 480;

	// OpenGL hints
	uint8 glVersionMajor = 3;
	uint8 glVersionMinor = 3;

	// buffer hints
	uint8 redBits	= 8;
	uint8 blueBits = 8;
	uint8 greenBits = 8;
	uint8 alphaBits = 8;
	uint8 depthBits = 24;
	uint8 stencilBits = 8;
};

/*
 *
 * name: Display
 *
 * @depends GLFW
 *
 * Acts as a wrapper class around a GLFW window.
 *
 * TODO: Get rid of `Display::Clear`
 * I don't want any direct OpenGL calls within
 * the Display; all of that should be left to
 * Graphics.
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

	void BindContext ();
	void Update ();

	inline const bool Running () const { return running; }
};

}
