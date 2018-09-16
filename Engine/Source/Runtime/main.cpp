#include <Raptor/Required.h>

#include <Core/Plugins.h>

#include <Graphics/API.h>

#include <iostream>

class MyAPI : public GraphicsAPI
{
	virtual void Clear () override
	{
		std::cout << "API Clear" << '\n';
	}

	virtual void DrawIndexed () override
	{
		std::cout << "API Draw" << '\n';
	}
};

int32 main (int32 argc, cchar * argv)
{
	// Open Library

	Core::SharedLibrary lib;

	lib.Open("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so");

	// Load Symbols

	Create_T  * CreatePlugin  = (Create_T  *) lib.ProcAddress("CreatePlugin");
  Destroy_T * DestroyPlugin = (Destroy_T *) lib.ProcAddress("DestroyPlugin");

	Plugin * plugin = CreatePlugin();
	MyAPI api;

	plugin -> Execute(& api);

	DestroyPlugin(plugin);

  // Exit

	lib.Close();

	return 0;
}
