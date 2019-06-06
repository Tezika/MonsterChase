#include "stdafx.h"
#include "MemorySystem.h"
#include "HeapManager.h"
#include "Assert.h"
#include "FixedSizeAllocator.h"
#include <cmath>

namespace Engine
{
	HeapManager * s_pDefaultHeap;

#ifdef USE_FIXED_ALLOCATORS
	FSAInitData * s_pFSASizes = nullptr;
	FixedSizeAllocator ** s_pFixedSizeAllocators = nullptr;
	size_t s_numOfFSASize = 6;
	size_t s_maxFSASize = 256;
	size_t s_minFSASize = 8;
#endif

	bool InitializeMemorySystem( void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors )
	{
		// Create your HeapManager and FixedSizeAllocators
		// Create a heap manager for my custom heap.
		HeapManager * pHeapManager = HeapManager::Create( i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors );
		assert( pHeapManager );

		s_pDefaultHeap = pHeapManager;
#ifdef USE_FIXED_ALLOCATORS
		InitializeFixedSizeAllocators();
#endif // USE_FIXED_ALLOCATOR
		DEBUG_PRINT_ENGINE( "The memory management system initialized succuessfully!" );
		return true;
	}

	void Collect()
	{
		// coalesce free blocks
		// you may or may not need to do this depending on how you've implemented your HeapManager
		if (s_pDefaultHeap != nullptr)
		{
			s_pDefaultHeap->Collect();
		}
	}

	void DestroyMemorySystem()
	{
		// Destroy your HeapManager and FixedSizeAllocators
		// Destory FixedSizeAllocators
#ifdef USE_FIXED_ALLOCATORS
		FixedSizeAllocator * pTempAllocator;
		for (size_t i = 0; i < s_numOfFSASize; i++)
		{
			pTempAllocator = s_pFixedSizeAllocators[i];
			s_pFixedSizeAllocators[i] = nullptr;
			delete pTempAllocator;
		}
		delete s_pFixedSizeAllocators;
#endif
		// Destory the heap manager
		assert( s_pDefaultHeap != nullptr );
		s_pDefaultHeap->Destroy();
		DEBUG_PRINT_ENGINE( "The memory management system destroied succuessfully!" );
	}

	HeapManager * GetDefaultHeap()
	{
		return s_pDefaultHeap;
	}

#ifdef USE_FIXED_ALLOCATORS
	bool InitializeFixedSizeAllocators()
	{
		bool successful = InitializeFSAInitData();
		assert( successful );
		s_pFixedSizeAllocators = reinterpret_cast< FixedSizeAllocator ** >( s_pDefaultHeap->Alloc( sizeof( FixedSizeAllocator * ) * s_numOfFSASize ) );
		assert( s_pFixedSizeAllocators );
		for (size_t i = 0; i < s_numOfFSASize; i++)
		{
			FixedSizeAllocator * pAllocator = FixedSizeAllocator::Create( s_pFSASizes[i].sizeBlock, s_pFSASizes[i].numBlocks, s_pDefaultHeap );
			assert( pAllocator );
			s_pFixedSizeAllocators[i] = pAllocator;
		}
		DEBUG_PRINT_ENGINE( "The fixed allocators initialized succuessfully!" );
		return true;
	}

	bool InitializeFSAInitData()
	{
		s_pFSASizes = reinterpret_cast< FSAInitData * >( s_pDefaultHeap->Alloc( sizeof( FSAInitData ) * s_numOfFSASize ) );
		assert( s_pFSASizes );
		//For test, the size of block are 8, 16, 32, 64, 128, 256. the number of blocks is 500
		for (size_t i = 0; i < s_numOfFSASize; i++)
		{
			s_pFSASizes[i].sizeBlock = ( size_t )pow( 2, i + 3 );
			s_pFSASizes[i].numBlocks = 500;
		}
		return true;
	}

	FixedSizeAllocator * FindFixedSizeAllocator( size_t i_size )
	{
		if (i_size == 0)
		{
			return nullptr;
		}

		if (i_size > s_maxFSASize)
		{
			return nullptr;
		}
		else if (i_size <= s_minFSASize)
		{
			return s_pFixedSizeAllocators[0];
		}
		else
		{
			for (size_t i = 0; i < s_numOfFSASize - 1; i++)
			{
				// check if the size is within two FSA size.
				if (i_size > s_pFSASizes[i].sizeBlock && i_size <= s_pFSASizes[i + 1].sizeBlock)
				{
					return s_pFixedSizeAllocators[i + 1];
				}
			}
		}
		return nullptr;
	}

	bool FreeFromFixedSizeAllocators( void * i_ptr )
	{
		assert( i_ptr != nullptr );
		bool successful = false;
		for (size_t i = 0; i < s_numOfFSASize; i++)
		{
			if (s_pFixedSizeAllocators[i] == nullptr)
			{
				continue;
			}
			successful = s_pFixedSizeAllocators[i]->Free( i_ptr );
			if (successful)
			{
				break;
			}
		}
		return successful;
	}
#endif // USE_FIXED_ALLOCATOR
}