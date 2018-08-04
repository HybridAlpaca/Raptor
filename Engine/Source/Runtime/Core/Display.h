#pragma once

class GLFWwindow {};

class Display
{
	GLFWwindow * window;
	
	static void FBSizeCallback (GLFWwindow * window, int width, int height);

public:

	Display ();
	Display (const Display & copy) = delete;
	~Display ();
	
	Display & operator= (const Display & rhs) = delete;
	
	void Update () const;
	bool ShouldClose () const;
	
	GLFWwindow * Window () const { return window; }
};
