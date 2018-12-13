#pragma once
#include <inttypes.h>

namespace Engine
{
	class HeapManager;
	class BitArray;

	class FixedSizeAllocator
	{
	public:
		static FixedSizeAllocator * Create(size_t i_sizeOfBlock, size_t i_numOfBlocks, HeapManager * i_pDefaultHeap);

		void * Alloc();
		bool Free(void * i_ptr);

		~FixedSizeAllocator();

		inline const size_t GetSize() { return m_sizeOfBlock; }

	private:
		FixedSizeAllocator() {};
		FixedSizeAllocator(size_t i_sizeOfBlock, size_t i_numOfBlocks, HeapManager * i_pDefaultHeap) {};
		FixedSizeAllocator(const FixedSizeAllocator & i_other) {};
		FixedSizeAllocator & operator=(const FixedSizeAllocator & i_other) {};

		size_t m_sizeOfBlock;
		size_t m_numOfBlocks;
		BitArray * m_pAllocationBitsArray;
		uint8_t * m_pAllocateMemory;
	};
}
