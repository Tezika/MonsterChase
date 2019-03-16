#include "stdafx.h"
#include "FixedAllocators.h"
#include <inttypes.h>
#include <stdio.h>
#include "FixedSizeAllocator.h"
#include "MemorySystem.h"
#include "HeapManager.h"

#ifdef USE_CUSTOM_MEMORYMANAGEMENT
void * __cdecl myMalloc( size_t i_size )
{
#ifdef OUTPUT_ALLOC_INFO
	DEBUG_PRINT_ENGINE( "malloc %zu bytes", i_size );
#endif // OUTPUT_ALLOC_INFO

	void * pReturn = nullptr;
#ifdef USE_FIXED_ALLOCATORS
	Engine::FixedSizeAllocator * pFSA = Engine::FindFixedSizeAllocator( i_size );
	if ( pFSA )
		pReturn = pFSA->Alloc();
	if ( pReturn == nullptr )
	{
		pReturn = Engine::GetDefaultHeap()->Alloc( i_size );
	}
#else
	pReturn = Engine::GetDefaultHeap()->Alloc( i_size );
#endif
	return pReturn;
}

void __cdecl myFree( void * i_ptr )
{
#ifdef  OUTPUT_ALLOC_INFO
	DEBUG_PRINT_ENGINE( "free 0x%" PRIXPTR "", reinterpret_cast<uintptr_t>( i_ptr ) );
#endif // OUTPUT_ALLOC_INFO
#ifdef USE_FIXED_ALLOCATORS
	bool successful = Engine::FreeFromFixedSizeAllocators( i_ptr );
	if ( !successful )
	{
		Engine::GetDefaultHeap()->Free( i_ptr );
	}
#else
	Engine::GetDefaultHeap()->Free( i_ptr );
#endif
}

void * operator new( size_t i_size )
{
	return myMalloc( i_size );
}

void operator delete( void * i_ptr )
{
	return myFree( i_ptr );
}

void * operator new[]( size_t i_size )
{
	// Since there is only new char[] in the unitest file, I don't need to deal with different types of new[]. 
	// Here I just wonder that if we need to deal with, what's way can we choose to make it. Overriding the new[] for every class we want to new?
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf( "new [] %zu\n", i_size );
	return myMalloc( i_size );
}

void operator delete[]( void * i_ptr )
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	// There is the same reason of the new[]
	printf( "delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>( i_ptr ) );
	return myFree( i_ptr );
}
#endif // USE_CUSTOM_MEMORYMANAGEMENT

