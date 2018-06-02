#pragma once

#include <Core/Common/Required.h>

namespace Core::Memory
{

// byte conversion utilities
static const size_t Kilobytes (const size_t bytes) { return bytes * 1000; }
static const size_t Megabytes (const size_t bytes) { return bytes * 1000 * 1000; }
static const size_t Gigabytes (const size_t bytes) { return bytes * 1000 * 1000 * 1000; }

static const size_t CalculatePadding (const size_t base_addr, const size_t alignment)
{
	const size_t
		multiplier = (base_addr / alignment) + 1,
		alignedAddr = multiplier * alignment,
		padding = alignedAddr - base_addr;
		
	return padding;
}

static const size_t CalculatePaddingWithHeader(const size_t baseAddress, const size_t alignment, const size_t headerSize)
{
	size_t padding = CalculatePadding(baseAddress, alignment);
	size_t neededSpace = headerSize;

	if (padding < neededSpace)
	{
		// Header does not fit - Calculate next aligned address that header fits
		neededSpace -= padding;

		// How many alignments I need to fit the header        
		if (neededSpace % alignment > 0)
		{
			padding += alignment * (1 + (neededSpace / alignment));
		}
		else
		{
			padding += alignment * (neededSpace / alignment);
		}
	}

	return padding;
}

}