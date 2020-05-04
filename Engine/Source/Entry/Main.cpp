#include <Common/Required.h>
#include <Common/String.h>

#include <Kernel/SharedLib.h>
#include <Kernel/ThreadPool.h>

#include <Graphics/SwapChain.h>

int32 main (int32 argc, cchar * argv)
{
	constexpr auto binDir = Std::String("/home/cellman123/Desktop/Raptor/Binaries/Debug/");
	constexpr auto graphicsPath = binDir + Std::String("libGraphics.so");

	Kernel::SharedLib graphics{graphicsPath.Data()};

	using CreateT = void (const Graphics::SwapChainDesc &);

	CreateT * foo = (CreateT *) graphics.ProcAddress("CreateSwapChain");

	Graphics::SwapChainDesc desc{800, 600, "Foo"};

	if (foo) foo(desc);

	Kernel::ThreadPool pool{3};

	pool.WaitAll();

	return 0;
}
