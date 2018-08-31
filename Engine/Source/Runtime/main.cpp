#include <Core/Common/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

cchar vertex = "#version 330 core\n"
"void main () {\n"
"return 0;\n"
"}\n";

cchar fragment = "#version 330 core\n"
"void main () {\n"
"return 0;\n"
"}\n";

int32 main (int32 argc, cchar * argv)
{
	Graphics::Display display
	({
		"Hello, Raptor!",
		800,
		600,
		3,
		3
	});

	Graphics::Backend::Init();
	Graphics::Backend::Resize(display.FrameWidth(), display.FrameHeight());

	uint32 shader = Graphics::Backend::AllocateShaderProgram(vertex, fragment);

	while (!display.Closed())
	{
		display.PollEvents();

		Graphics::Backend::Clear(1.0f, 0.0f, 0.5f, 1.0f);
		Graphics::Backend::Present(display);
	}

	Graphics::Backend::DestroyShaderProgram(shader);

	return 0;
}
