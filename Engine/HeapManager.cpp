#include "stdafx.h"
#include "assert.h"
#include "HeapManager.h"

Engine::HeapManager::HeapManager()
{
	pFreeDesciptorList_ = new TList<BlockDescriptor>();
	pFreeMemoryList_ = new TList<BlockDescriptor>();
	pOutstandingAllocationList_ = new TList<BlockDescriptor>();
}

Engine::HeapManager::~HeapManager()
{
}

Engine::HeapManager* Engine::HeapManager::Create(void* i_pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
{
	assert(i_pMemory);
	return nullptr;
}

void Engine::HeapManager::Destroy()
{
}

void* Engine::HeapManager::Alloc(size_t i_size)
{

	return nullptr;
}

void* Engine::HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool Engine::HeapManager::Free(void* i_ptr)
{
	assert(i_ptr);
	return true;
}