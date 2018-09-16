#include <Raptor/Required.h>
#include <Graphics/API.h>

#include <dlfcn.h>
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

	void * library = dlopen("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so", RTLD_LAZY);
	if (!library)
	{
		std::cerr << dlerror() << '\n';
		return 1;
	}

	// Load Symbols

	Create_T * CreatePlugin = (Create_T *) dlsym(library, "CreatePlugin");
  Destroy_T * DestroyPlugin = (Destroy_T *) dlsym(library, "DestroyPlugin");

  // Check for errors

  cchar dlsym_error = dlerror();
  if (dlsym_error) {
      std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
      dlclose(library);
      return 1;
  }

	Plugin * plugin = CreatePlugin();
	MyAPI api;

	plugin -> Execute(& api);

	DestroyPlugin(plugin);

  // Exit

	dlclose(library);

	return 0;
}
