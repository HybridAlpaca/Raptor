#pragma once

#include <Raptor/Required.h>

#ifdef WIN32
# define EXPORT __declspec(dllexport)
#else
# define EXPORT // empty
#endif

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

	virtual uint16 CreateShader (cchar vertexCode, cchar fragmentCode) = 0;
	virtual void DestroyShader (uint16 shader) = 0;

	virtual uint16 CreateVertexArray () = 0;
	virtual void DestroyVertexArray (uint16 vertexArray) = 0;

	virtual uint16 CreateBuffer (uint16 vertexArray, void * data, uint16 type, uintptr size, uint8 * attribs, uint16 attribCount) = 0;
	virtual void DestroyBuffer (uint16 buffer) = 0;

	virtual void DrawIndexed (uint16 vertexArray, uint16 shader, uint16 indexCount) = 0;

	//

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
	virtual void Update (float32 delta) = 0;
	virtual void Shutdown () = 0;
};

struct PluginDescriptor
{
	typedef Plugin * (* GetPluginFunc)();

	cchar className;
	cchar pluginName;

	uint32 pluginVersionMajor;
	uint32 pluginVersionMinor;

	GetPluginFunc CreatePlugin;
};

#define EXPORT_PLUGIN(CLASS_TYPE, PLUGIN_NAME, VERSION_MAJOR, VERSION_MINOR) \
extern "C" \
{ \
	EXPORT Plugin * GetPlugin() \
	{ \
		static CLASS_TYPE singleton; \
		return & singleton; \
	} \
	EXPORT PluginDescriptor Exports = \
	{ \
		#CLASS_TYPE, \
		PLUGIN_NAME, \
		VERSION_MAJOR, \
		VERSION_MINOR, \
		GetPlugin \
	}; \
}
