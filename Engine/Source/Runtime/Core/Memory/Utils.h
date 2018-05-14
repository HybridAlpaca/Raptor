#pragma once

#include <Core/Misc/Required.h>

namespace Core
{
namespace Memory
{

static const size_t CalculatePadding (const size_t base_addr, const size_t alignment)
{
	const size_t
		multiplier = (base_addr / alignment) + 1,
		alignedAddr = multiplier * alignment,
		padding = alignedAddr - base_addr;
		
	return padding;
}

}
}