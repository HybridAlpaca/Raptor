#include <Graphics/API.h>

struct GraphicsPlugin : public Plugin
{
	virtual void Execute (GraphicsAPI * api) override
	{
		api -> Clear();
		api -> DrawIndexed();
		api -> DrawIndexed();
		api -> DrawIndexed();
	}
};

extern "C" Plugin * CreatePlugin ()
{
	return new GraphicsPlugin;
}

extern "C" void DestroyPlugin (Plugin * plugin)
{
	delete plugin;
}
