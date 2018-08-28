#pragma once

#include "RenderDevice.h"
#include "../Commands.h"

namespace Graphics::Backend
{

void DrawIndexed (RenderDevice & device, const DrawPacket & packet)
{
	const Commands::DrawIndexed & command = packet.data.drawIndexed;
	device.BindVAO(command.vertexArray);
}

}
