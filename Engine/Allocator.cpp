#include "stdafx.h"
#include "Allocator.h"
#include "HeapManager.h"

void * operator new(size_t i_size)
{
	return nullptr;
}

void operator delete(void * i_ptr)
{
}

void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Allocated new memory, size is %d, from the file %s and the line %d,", i_size, i_pFile, i_Line);
	return nullptr;
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	DEBUG_PRINT("Freed the memory, 0x%p, from the file %s and the line %d,", i_ptr, i_pFile, i_Line);
}

void * alloc(const Engine::HeapManager* i_pHeapManager, size_t i_size)
{
	return nullptr;
}

void * alloc(const Engine::HeapManager * i_pHeapManager, size_t i_size, unsigned int alignment)
{
	return nullptr;
}