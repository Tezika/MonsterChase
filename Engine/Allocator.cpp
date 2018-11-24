#include "stdafx.h"
#include "Allocator.h"

void * operator new(size_t i_size)
{
	return nullptr;
}

void operator delete(void * i_ptr)
{
	
}

void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	return nullptr;
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{

}