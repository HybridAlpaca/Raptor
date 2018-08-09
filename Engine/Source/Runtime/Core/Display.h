#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 *
 * @class Display
 * @headerfile Display.h <Core/Display.h>
 * @author Seth Traman
 * @date August 2018
 * 
 * @brief RAII wrapper around GLFW window instance 
 * 
 **/

class Display
{
	/// Internal GLFW window instance
	GLFWwindow * window;
	
	/// Framebuffer resize callback
	/// @deprecated
	static void FBSizeCallback (GLFWwindow * window, int width, int height);

public:

	Display ();
	
	/// @brief Noncopyable
	Display (const Display & copy) = delete;
	
	/// @brief Destroys internal window and frees OpenGL context
	~Display ();
	
	/// @brief Noncopyable
	Display & operator= (const Display & rhs) = delete;
	
	/// @brief Responsible for polling window events and drawing to physical screen
	void Update () const;
	
	/// @brief Checks if the window's closed
	/// @return Whether GLFW has determined the window is ready to be closed or not
	bool ShouldClose () const;
	
	/// @brief Getter method
	/// @deprecated This method will become obsolete and ultimately be removed once a functioning input / event system is implemented.
	/// @return Pointer to internal GLFW window instance
	GLFWwindow * Window () const { return window; }
};
