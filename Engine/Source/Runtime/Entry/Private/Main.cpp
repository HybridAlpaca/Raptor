#include <Kernel/Kernel.h>

int main (int argc, char ** argv)
{
	Core::Kernel kernel;

	kernel.Create();

	return kernel.Destroy();
}
