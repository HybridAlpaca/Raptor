#include <Commands.h>
#include <RenderDevice.h>

using namespace Graphics;
using namespace Graphics::Commands;

Clear::DispatchFunc Clear::Dispatch = RenderDevice::Clear;
Draw::DispatchFunc Draw::Dispatch = RenderDevice::Draw;
DrawIndexed::DispatchFunc DrawIndexed::Dispatch = RenderDevice::DrawIndexed;
