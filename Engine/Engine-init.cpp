#include "stdafx.h"
#include "Engine-init.h"
#include "ConsolePrint.h"
#include "Assert.h"
#include "HeapManager.h"
#include <Windows.h>

namespace Engine
{
	bool Engine::Initialize()
	{
		const size_t 		sizeHeap = 1024 * 1024;
		const unsigned int 	numDescriptors = 2048;

		// Allocate memory for my custom heap.
		void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
		assert(pHeapMemory);

		// Create a heap manager for my custom heap.
		HeapManager * pHeapManager = HeapManager::Create(pHeapMemory, sizeHeap, numDescriptors);
		assert(pHeapManager);

		if (pHeapManager == nullptr)
			return false;

		HeapManager::s_pHeapManager = pHeapManager;
		DEBUG_PRINT("The engine initialized succuessfully!");
		return true;
	}

	void Engine::Destroy()
	{
		//free my cust heap and destroy the heap
		assert(HeapManager::s_pHeapManager);
		HeapManager::s_pHeapManager->Destroy();
		HeapFree(GetProcessHeap(), 0, HeapManager::s_pHeapManager->GetAssociateMemory());
		HeapManager::s_pHeapManager = nullptr;
		DEBUG_PRINT("The engine destroied successfully!");
	}
}
