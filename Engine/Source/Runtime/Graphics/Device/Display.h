#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Graphics::Device
{

class Display
{
	GLFWwindow * window;
	bool closed;

public:

	Display (uint16 width, uint16 height, cchar title);
	Display (const Display & copy) = delete;
	~Display ();
	
	Display & operator= (const Display & rhs) = delete;

	void Clear (float r, float g, float b, float a);
	void Update ();
	
	const bool Closed () const { return closed; }

};

}