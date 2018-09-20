#include <SharedLib.h>

#include <dlfcn.h>
#include <iostream>

using namespace Core;

void SharedLibrary::Open (cchar path)
{
	handle = dlopen(path, RTLD_LAZY);
	if (!handle)
	{
		std::cerr << dlerror() << '\n';
	}
}

void SharedLibrary::Close ()
{
	dlclose(handle);
}

void * SharedLibrary::ProcAddress (cchar symbol)
{
	void * result = dlsym(handle, symbol);

	cchar dlsym_error = dlerror();

  if (dlsym_error)
  {
      std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
      Close();
  }

	return result;
}
