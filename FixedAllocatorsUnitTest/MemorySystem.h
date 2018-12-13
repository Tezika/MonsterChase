#pragma once

namespace Engine
{
	class HeapManager;


#ifdef USE_FIXED_ALLOCATOR
	struct FSAInitData
	{
		size_t	sizeBlock;
		size_t	numBlocks;
	};

	bool InitializeFixedSizeAllocators();
	FixedSizeAllocator * CreateFixedSizeAllocator(size_t i_sizeOfBlock, size_t i_numOfBlocks);

#endif;

	// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
	bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

	// Collect - coalesce free blocks in attempt to create larger blocks
	void Collect();

	// DestroyMemorySystem - destroy your memory systems
	void DestroyMemorySystem();

	HeapManager * GetDefaultHeap();
}



