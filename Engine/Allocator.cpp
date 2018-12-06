#include "stdafx.h"
#include "Allocator.h"
#include "Assert.h"
#include "HeapManager.h"

#ifdef USE_CUSTOM_ALLOCATE
void * operator new(size_t i_size)
{
	DEBUG_PRINT("Allocated new memory, size is %d.", i_size);
	assert(Engine::HeapManager::s_pDefalutHeapManager);
	void * memory = _alloc(i_size);
	assert(memory);
	return memory;
}

void operator delete(void * i_ptr)
{
	assert(Engine::HeapManager::s_pDefalutHeapManager);
	_free(i_ptr);
}

void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Allocated new memory, size is %d, from the file %s and the line %d,", i_size, i_pFile, i_Line);
	assert(Engine::HeapManager::s_pDefalutHeapManager);
	void * memory = _alloc(i_size);
	assert(memory);
	return memory;
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Freed the memory, 0x%p, from the file %s and the line %d,", i_ptr, i_pFile, i_Line);
	assert(Engine::HeapManager::s_pDefalutHeapManager);
	_free(i_ptr);
}

void * operator new(size_t i_size, Engine::HeapManager * pHeapManager)
{
	DEBUG_PRINT("Allocated new memory, size is %d from the heap, 0x%p", i_size, pHeapManager);
	assert(pHeapManager);
	void * memory = pHeapManager->Alloc(i_size);
	assert(memory);
	return memory;
}

void operator delete(void * i_ptr, Engine::HeapManager * pHeapManager)
{
	DEBUG_PRINT("Freed the memory, 0x%p, from the heap, 0x%p", i_ptr, pHeapManager);
	assert(pHeapManager);
	pHeapManager->Free(i_ptr);
}
#endif
