#pragma once

#include <Raptor/Required.h>

#define EXPORT_PLUGIN(PLUGIN_NAME) \
	extern "C" Plugin * CreatePlugin () { return new PLUGIN_NAME; } \
	extern "C" void DestroyPlugin (Plugin * plugin) { delete plugin; plugin = nullptr; }

/**
 *
 * @class GraphicsApi
 * @author Seth Traman
 * @brief Abstract class describig the methods a graphics API is expected to have
 *
 **/
class GraphicsApi
{

public:

	virtual ~GraphicsApi () {}

	virtual void Clear (float32 color [4]) = 0;
};

/// An enum defining the types of API's a plugin may request

enum class EngineApi
{
	GRAPHICS ///< Requests an instance of the engine's graphics API
};

/// Function pointer provided to plugin on startup that allows it to query for engine API's
using EngineApiGetter = void * (EngineApi api, uint32 version);

/**
 *
 * @struct Plugin
 * @author Seth Traman
 * @brief Abstract class that a plugin author may inherit from to create or extend engine functionality
 *
 **/
class Plugin
{

public:

	virtual ~Plugin () {}

	virtual void Init (EngineApiGetter getEngineApi) = 0;
	virtual void Update () = 0;
	virtual void Shutdown () = 0;
};

/// Function pointer the engine uses to create instances of a plugin
using Create_T =  Plugin * ();

/// Counterpart of Create_T, the engine uses this to destroy plugin instances
using Destroy_T = void (Plugin *);
