#pragma once

#include "DeviceState.h"
#include "../DrawContext.h"

/*
 *
 * RENDER DEVICE DESIGN DECISIONS
 *
 *
 * Current implementation:
 * - Load raw data into memory
 * - Transform data into rendering instructions (packets)
 * - Send packets to a backend (RenderDevice) for sequential execution
 *
 * PROS:
 * - Allows for easy multithreading, as data read / writes are very controlled
 * - Low memory footprint: each command is a POD
 *
 * CONS:
 * - Resource management can become a pain :(
 *
 *
 * Alternative implementation:
 * - Get rid of render device (?)
 * - Assign function pointers (dispatches) to packets
 * - Dispatches use command data to execute draw calls
 *
 * PROS:
 * - Same benefits as before
 * - Much more versatile rendering system; allows for user-defined data execution
 *
 * CONS:
 * - Higher overhead; each packet stores an additional 4-8 bytes
 * - Slightly slower execution due to function pointer calls
 *
 */

namespace Graphics::Backend::GL
{

class RenderDevice
{
	DeviceState state;

public:

	RenderDevice ();
	RenderDevice (const RenderDevice & copy) = delete;
	~RenderDevice ();

	RenderDevice & operator= (const RenderDevice & rhs) = delete;

	/// Executes OpenGL draw calls based on information in draw context
	void Dispatch (const DrawContext & ctx);
};

}
