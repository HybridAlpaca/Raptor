#include <SharedLib.h>

#include <dlfcn.h>

using namespace Kernel;

SharedLib::SharedLib (cchar path)
{
	handle = (uint64) dlopen(path, RTLD_LAZY);

	if (handle) loaded = true;
}

SharedLib::SharedLib (SharedLib && rvalue)
{
	handle = rvalue.handle;
	rvalue.handle = 0;

	loaded = rvalue.loaded;
	rvalue.loaded = false;
}

SharedLib::~SharedLib ()
{
	if (loaded)
	{
		dlclose((void *) handle);
	}
}

SharedLib & SharedLib::operator= (SharedLib && rhs)
{
	handle = rhs.handle;
	rhs.handle = 0;

	loaded = rhs.loaded;
	rhs.loaded = false;

	return (* this);
}

void * SharedLib::ProcAddress (cchar symbol)
{
	if (!loaded) return nullptr;

	void * addr = dlsym((void *) handle, symbol);

	cchar error = dlerror();

	return (error) ? nullptr : addr;
}
