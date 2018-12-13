#pragma once
#include <inttypes.h>
class BitArray;
class HeapManager;

class FixedSizeAllocator
{
public:
	static FixedSizeAllocator * Create(size_t i_sizeOfBlock, size_t i_numOfBlocks, void * i_pDefaultHeap);
	FixedSizeAllocator(size_t i_sizeOfBlock, size_t i_numOfBlocks, void * i_pDefaultHeap);
	FixedSizeAllocator(const FixedSizeAllocator & i_other);
	FixedSizeAllocator & operator=(const FixedSizeAllocator & i_other);

	void * Alloc();
	bool Free(void * i_ptr);

	~FixedSizeAllocator();

	inline const size_t GetSize() { return m_sizeOfBlock; }
private:
	FixedSizeAllocator() {};

	size_t m_sizeOfBlock;
	size_t m_numOfBlocks;
	BitArray * m_pAllocationBitsArray;
	uint8_t * m_pAllocateMemory;
};