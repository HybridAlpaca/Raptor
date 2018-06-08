#pragma once

#include <Core/Common/Required.h>

namespace Core::Backend
{

/*
 * 
 * name: AppConfigData
 * 
 * Stores options and parameters used for
 * initializing the application.
 * 
 */


struct AppConfigData
{
	cchar title = "[application title]";
	uint32 width = 640;
	uint32 height = 480;
	uint8 versionMajor = 1;
	uint8 versionMinor = 0;
	uint8 versionPatch = 0;
};

/*
 *
 * name: Application
 * @depends GLFW
 *
 * Manages SDL subsystems for use in other
 * engine systems, i.e. Graphics::Display.
 *
 */
class Application
{
	AppConfigData config;
	
	bool running = true;
	
public:

	Application (const AppConfigData & config);
	Application (const Application & copy) = delete;
	~Application ();

	Application & operator= (const Application & rhs) = delete;
	
	void Destroy ();
	
	const AppConfigData Config () const { return config; }
	
	const bool Running () const { return running; }
	void Running (bool val) { running = val; }
};

}
