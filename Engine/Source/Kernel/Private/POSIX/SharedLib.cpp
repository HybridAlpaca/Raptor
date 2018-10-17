#include <SharedLib.h>

#include <dlfcn.h>

using namespace Kernel;

SharedLib::SharedLib (cchar path)
{
	handle = dlopen(path, RTLD_LAZY);
	if (!handle)
	{
		// Requested DLL cannot be opened
		loaded = false;
	}
	else
	{
		loaded = true;
	}
}

SharedLib::SharedLib (SharedLib && rvalue)
{
	handle = rvalue.handle;
	rvalue.handle = nullptr;

	loaded = rvalue.loaded;
	rvalue.loaded = false;
}

SharedLib::~SharedLib ()
{
	if (loaded) dlclose(handle);
}

SharedLib & SharedLib::operator= (SharedLib && rhs)
{
	handle = rhs.handle;
	rhs.handle = nullptr;

	loaded = rhs.loaded;
	rhs.loaded = false;

	return (* this);
}

void * SharedLib::ProcAddress (cchar symbol)
{
	if (!loaded) return nullptr;

	void * addr = dlsym(handle, symbol);

	cchar dlsym_error = dlerror();
	if (dlsym_error)
	{
		// Requested symbol cannot be found in the opened DLL
		return nullptr;
	}

	return addr;
}
