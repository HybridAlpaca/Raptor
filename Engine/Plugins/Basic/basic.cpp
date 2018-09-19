#include <Core/PluginsApi.h>

#include <iostream>

class BasicPlugin : public Plugin
{
	GraphicsApi * graphics = nullptr;

	const uint32 GRAPHICS_API_VERSION = 0;

	float32 clearColor [4] = { 0.2f, 1.0f, 0.2f, 1.0f };

public:

	virtual void Init (EngineApiGetter GetEngineApi) override
	{
		// For now, it's safe to assume getEngineApi won't return nullptr (given the proper version), so we won't check for errors.

		graphics = (GraphicsApi *) GetEngineApi(EngineApi::GRAPHICS, GRAPHICS_API_VERSION);
	}

	virtual void Update () override
	{
		graphics -> Clear(clearColor);
	}

	virtual void Shutdown () override
	{
		/// @todo something
	}
};

EXPORT_PLUGIN(BasicPlugin)
