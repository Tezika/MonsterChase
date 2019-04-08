#pragma once

namespace Engine
{
	class HeapManager;
	class FixedSizeAllocator;

//#define USE_CUSTOM_MEMORYMANAGEMENT
//#define USE_FIXED_ALLOCATORS
//#define OUTPUT_ALLOC_INFO

#ifdef _DEBUG
#ifdef USE_CUSTOM_MEMORYMANAGEMENT
#define TRACK_NEW (__FILE__,__LINE__)
#else
#define TRACK_NEW
#endif
#else
#define TRACK_NEW
#endif

#ifdef USE_FIXED_ALLOCATORS
	struct FSAInitData
	{
		size_t	sizeBlock;
		size_t	numBlocks;
	};

	bool InitializeFixedSizeAllocators();
	bool InitializeFSAInitData();
	FixedSizeAllocator * FindFixedSizeAllocator( size_t i_size );

	bool FreeFromFixedSizeAllocators( void * i_ptr );
#endif;

	// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
	bool InitializeMemorySystem( void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors );

	// Collect - coalesce free blocks in attempt to create larger blocks
	void Collect();

	// DestroyMemorySystem - destroy your memory systems
	void DestroyMemorySystem();

	HeapManager * GetDefaultHeap();
}
