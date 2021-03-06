#include "stdafx.h"
#include "FixedAllocators.h"
#include <inttypes.h>
#include <stdio.h>
#include "FixedSizeAllocator.h"
#include "MemorySystem.h"
#include "HeapManager.h"

#ifdef USE_CUSTOM_MEMORYMANAGEMENT
void * __cdecl malloc_c( size_t i_size )
{
	using namespace Engine;
	void * pReturn = nullptr;
#ifdef USE_FIXED_ALLOCATORS
	FixedSizeAllocator * pFSA = Engine::FindFixedSizeAllocator( i_size );
	if (pFSA)
		pReturn = pFSA->Alloc();
	if (pReturn == nullptr)
	{
		// Allocate the actual memory based on the alignment of 16.
		pReturn = GetDefaultHeap()->Alloc( i_size, HeapManager::s_alignment );
	}
#ifdef OUTPUT_ALLOC_INFO
#ifdef ALIGNMENT_ALLOCATION
	// If the heap manager allocate the memory based on the aligment, it should calculate the actual memory size.
	i_size = (static_cast< size_t >((sizeof( BlockDescriptor ) + i_size) / HeapManager::s_alignment) + 1) *  HeapManager::s_alignment;
#else
#endif
	DEBUG_PRINT_ENGINE( "malloc %zu bytes on 0x%" PRIXPTR"", pFSA == nullptr ? i_size : pFSA->GetSize(), reinterpret_cast< uintptr_t >(pReturn) );
#endif // OUTPUT_ALLOC_INFO
#else
	pReturn = Engine::GetDefaultHeap()->Alloc( i_size, HeapManager::s_alignment );
#ifdef OUTPUT_ALLOC_INFO
#ifdef ALIGNMENT_ALLOCATION
	// If the heap manager allocate the memory based on the aligment, it should calculate the actual memory size.
	i_size = (static_cast< size_t >((sizeof( BlockDescriptor ) + i_size) / HeapManager::s_alignment) + 1) *  HeapManager::s_alignment;
#else
#endif
	DEBUG_PRINT_ENGINE( "malloc %zu bytes on 0x%" PRIXPTR"", pFSA == nullptr ? i_size : pFSA->GetSize(), reinterpret_cast< uintptr_t >(pReturn) );
#endif // OUTPUT_ALLOC_INFOOUTPUT_ALLOC_INFO
#endif
	return pReturn;
}

void __cdecl free_c( void * i_ptr )
{
	if (i_ptr == nullptr)
	{
		return;
	}
	using namespace Engine;
#ifdef  OUTPUT_ALLOC_INFO
	DEBUG_PRINT_ENGINE( "free 0x%" PRIXPTR "", reinterpret_cast< uintptr_t >(i_ptr) );
#endif // OUTPUT_ALLOC_INFO
#ifdef USE_FIXED_ALLOCATORS
	bool successful = FreeFromFixedSizeAllocators( i_ptr );
	if (!successful)
	{
		/*assert( Engine::GetDefaultHeap()->Free( i_ptr ) );*/
		GetDefaultHeap()->Free( i_ptr );
}
#else
	//assert( Engine::GetDefaultHeap()->Free( i_ptr ) );
	GetDefaultHeap()->Free( i_ptr );
#endif
}

void * operator new(size_t i_size)
{
	return malloc_c( i_size );
}

void operator delete(void * i_ptr)
{
	return free_c( i_ptr );
}

void * operator new[]( size_t i_size )
{
	// Since there is only new char[] in the unitest file, I don't need to deal with different types of new[]. 
	// Here I just wonder that if we need to deal with, what's way can we choose to make it. Overriding the new[] for every class we want to new?
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf( "new [] %zu\n", i_size );
	return malloc_c( i_size );
}

void operator delete[]( void * i_ptr )
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	// There is the same reason of the new[]
	printf( "delete [] 0x%" PRIXPTR "\n", reinterpret_cast< uintptr_t >(i_ptr) );
	return free_c( i_ptr );
}
#endif // USE_CUSTOM_MEMORYMANAGEMENT
