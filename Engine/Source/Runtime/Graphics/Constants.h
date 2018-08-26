#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{

/// Each render command should be indexable via an 8-bit int
const uint8 MAX_RENDER_DRAW_COMMANDS = 255;

const uint8 MAX_RENDER_RESOURCE_COMMANDS = 255;

namespace Backend
{

/// Each render resource should be indexable via a 16-bit int
const uint16 MAX_RENDER_RESOURCES = 65535;

}

}
