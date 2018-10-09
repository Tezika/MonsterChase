#include "stdafx.h"
#include "HeapManager.h"

Engine::HeapManager::HeapManager()
{
}

Engine::HeapManager::~HeapManager()
{
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
	return true;
}


