template <typename Type>
Type * Core::Memory::LinearAllocator::Allocate ()
{
	size_t
		padding = 0,
		paddedAddr = 0;
		
	const size_t currentAddr = (size_t) startPtr + offset;
	
	if (alignof(Type) != 0 && (offset % alignof(Type) != 0))
	{
		// bit padding is required to properly
		// align data
		padding = Core::Memory::CalculatePadding(currentAddr, alignof(Type));
	}
	
	if (offset + padding + sizeof(Type) > bufferSize)
	{
		// allocation size exceeded max buffer size
		DEBUG("possible segfault avoided.  Watch your allocations!");
		return nullptr;
	}
	
	offset += padding;
	const size_t nextAddr = currentAddr + padding;
	
	offset += sizeof(Type);
	memoryUsed = offset;
	
	if (memoryUsed > memoryPeak)
	{
		memoryPeak = memoryUsed;
	}
	
	return (Type *) nextAddr;
}