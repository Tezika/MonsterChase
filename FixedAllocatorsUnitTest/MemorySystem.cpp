#include "pch.h"
#include "MemorySystem.h"
#include "HeapManager.h"
#include "Assert.h"
#include "FixedSizeAllocator.h"

namespace Engine
{
	HeapManager * s_pDefaultHeap;

#ifdef USE_FIXED_ALLOCATOR
	FSAInitData s_FSASizes[];
	FixedSizeAllocator ** s_pFixedSizeAllocators;
#endif

	bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
	{
		// create your HeapManager and FixedSizeAllocators
		// Create a heap manager for my custom heap.
		HeapManager * pHeapManager = HeapManager::Create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
		assert(pHeapManager);

		s_pDefaultHeap = pHeapManager;
#ifdef USE_FIXED_ALLOCATOR
		InitializeFixedSizeAllocators();
#endif // USE_FIXED_ALLOCATOR
		DEBUG_PRINT("The memory system initialized succuessfully!");
		return true;
	}

	void Collect()
	{
		// coalesce free blocks
		// you may or may not need to do this depending on how you've implemented your HeapManager
	}

	void DestroyMemorySystem()
	{
		// Destroy your HeapManager and FixedSizeAllocators
		// Destory FixedSizeAllocators

		// Destory the heap manager
		assert(s_pDefaultHeap != nullptr);
		s_pDefaultHeap->Destroy();
		DEBUG_PRINT("The memory system destroied succuessfully!");
	}

	FixedSizeAllocator * CreateFixedSizeAllocator(size_t i_sizeOfBlock, size_t i_numOfBlocks)
	{
		return nullptr;
	}

	bool InitializeFixedSizeAllocators()
	{
		return true;
	}

	HeapManager * GetDefaultHeap()
	{
		return s_pDefaultHeap;
	}
}

