#include <Common/Required.h>
#include <Common/String.h>

#include <Kernel/SharedLib.h>
#include <Kernel/ThreadPool.h>

#include <Graphics/DrawContext.h>

int32 main (int32 argc, cchar * argv)
{
	constexpr auto binDir = Std::String("/home/cellman123/Desktop/Raptor/Binaries/Debug/");
	constexpr auto graphicsPath = binDir + Std::String("libGraphics.so");

	Kernel::SharedLib graphics{graphicsPath.Data()};

	using CreateT = DrawContext * ();

	CreateT * create = (CreateT *) graphics.ProcAddress("CreateDrawContext");

	DrawContext * ctx;

	if (create) ctx = create();

	ctx -> Foo();

	Kernel::ThreadPool pool{3};

	pool.WaitAll();

	return 0;
}
