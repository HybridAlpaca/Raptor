#include <Common/Required.h>

#include <Kernel/ThreadPool.h>

int32 main (int32 argc, cchar * argv)
{
	Kernel::ThreadPool pool{3};

	pool.WaitAll();

	return 0;
}
