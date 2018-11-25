//Use this file to override the global new & delete
#pragma once
#include "HeapManager.h"

//#define USE_CUSTOM_ALLOCATE

#ifdef USE_CUSTOM_ALLOCATE
#ifndef _alloc
#define _alloc(_Size) alloc(pHeapManager, _Size)
#endif // !_alloc

#ifndef _aligned_alloc
#define _aligned_alloc(_Size, _Alignment) alloc(pHeapManager, _Size, _Alignment)
#endif // !aligned_alloc

#ifndef _free
#define _free(_Ptr)
#endif // !_free

#ifndef _aligned_free
#define _aligned_free
#endif // !_aligned_free

// TRACK NEW: only track in Debug build
#ifdef _DEBUG
#define TRACK_NEW (__FILE__,__LINE__)
#else
#define TRACK_NEW
#endif
	// standard allocators
void * operator new(size_t i_size);
void operator delete(void * i_ptr);

// tracking allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line);
void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line);

//Global alloc functions
void * alloc(const Engine::HeapManager* i_pHeapManager, size_t i_size);
void * alloc(const Engine::HeapManager * i_pHeapManager, size_t i_size, unsigned int alignment);
#endif // USE_CUSTOMALLOCATE
