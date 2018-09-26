#pragma once

#include <Raptor/Required.h>

#ifdef WIN32
# define EXPORT __declspec(dllexport)
#else
# define EXPORT // empty
#endif

class ApiRegistry
{
	static const uint16 MAX_API_COUNT = 65535;

	void * apiPool [MAX_API_COUNT] = { nullptr };

public:

	inline void RegisterApi (uint32 identifier, void * api)
	{
		apiPool[identifier] = api;
	}

	inline void * GetApi (uint32 identifier) const
	{
		return apiPool[identifier];
	}
};

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

	virtual void Init (const ApiRegistry & registry) = 0;
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
