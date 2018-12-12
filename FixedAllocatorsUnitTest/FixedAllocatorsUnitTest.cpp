// FixedAllocatorsUnitTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include "MemorySystem.h"

#include <assert.h>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <iostream>
#include "BitArray.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // _DEBUG


bool MemorySystem_UnitTest();
bool BitArray_UnitTest();

int main(int i_arg, char **)
{
	//	const size_t 		sizeHeap = 1024 * 1024;
	//
	//	// you may not need this if you don't use a descriptor pool
	//	const unsigned int 	numDescriptors = 2048;
	//
	//	// Allocate memory for my test heap.
	//	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	//	assert(pHeapMemory);
	//
	//	// Create your HeapManager and FixedSizeAllocators.
	//	InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
	//
	//	bool success = MemorySystem_UnitTest();
	//	assert(success);
	//
	//	// Clean up your Memory System (HeapManager and FixedSizeAllocators)
	//	DestroyMemorySystem();
	//
	//	HeapFree(GetProcessHeap(), 0, pHeapMemory);
	//
	//	// in a Debug build make sure we didn't leak any memory.
	//#if defined(_DEBUG)
	//	_CrtDumpMemoryLeaks();
	//#endif // _DEBUG
	//	
		//unsigned long mask = 0x1000;
		//unsigned long index;
		//unsigned char isNonzero;
		//while (1)
		//{
		//	std::cout << "Enter a positive integer as the mask: " << std::flush;
		//	std::cin >> mask;
		//	isNonzero = _BitScanForward(&index, mask);
		//	if (isNonzero)
		//	{
		//		std::cout << "Mask: " << mask << " Index: " <<63 -index << std::endl;
		//	}
		//	else
		//	{
		//		std::cout << "No set bits found.  Mask is zero." << std::endl;
		//	}
		//}
	BitArray_UnitTest();
	_getch();
	return 0;
}

bool MemorySystem_UnitTest()
{
	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	size_t totalAllocated = 0;
	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void * pPtr = malloc(sizeAlloc);

		// if allocation failed see if garbage collecting will create a large enough block
		if (pPtr == nullptr)
		{
			Collect();

			pPtr = new char[sizeAlloc];

			// if not we're done. go on to cleanup phase of test
			if (pPtr == nullptr)
				break;
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		totalAllocated += sizeAlloc;

		// randomly free and/or garbage collect during allocation phase
		const unsigned int freeAboutEvery = 0x07;
		const unsigned int garbageCollectAboutEvery = 0x07;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			free(pPtrToFree);
			numFrees++;
		}
		else if ((rand() % garbageCollectAboutEvery) == 0)
		{
			Collect();

			numCollects++;
		}

	} while (1);

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtrToFree = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			delete[] pPtrToFree;
		}

		// do garbage collection
		Collect();
		// our heap should be one single block, all the memory it started with

		// do a large test allocation to see if garbage collection worked
		void * pPtr = malloc(totalAllocated / 2);

		if (pPtr)
		{
			free(pPtr);
		}
		else
		{
			// something failed
			return false;
		}
	}
	else
	{
		return false;
	}

	// this new [] / delete [] pair should run through your allocator
	char * pNewTest = new char[1024];

	delete[] pNewTest;

	printf("Congrat! You passed the unit test.");
	// we succeeded
	return true;
}

bool BitArray_UnitTest()
{
	BitArray * arrTest = BitArray::Create(256, nullptr, true);
	assert(arrTest);
	assert(arrTest->AreAllClear());
	assert(!arrTest->AreAllSet());
	size_t bit_test;
	arrTest->SetBit(23);
	arrTest->GetFirstSetBit(bit_test);
	assert(!arrTest->AreAllClear());
	assert(!arrTest->AreAllSet());
	printf("%d", bit_test);
	return true;
}
