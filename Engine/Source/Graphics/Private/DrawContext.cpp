#include <DrawContext.h>

#include <iostream>

struct Oof : DrawContext
{
	void Foo () override
	{
		std::cout << "Foo\n";
	}
};

extern "C"
{
	DrawContext * CreateDrawContext ()
	{
		static Oof oof;

		return & oof;
	}

	void DestroyDrawContext (DrawContext * ctx)
	{
		// Do nothing
	}
}
