//Use this file to override the global new & delete
#pragma once
class HeapManager;

#define USE_CUSTOM_ALLOCATE

// TRACK NEW: only track in Debug build
#ifdef _DEBUG
#ifdef USE_CUSTOM_ALLOCATE
#define TRACK_NEW (__FILE__,__LINE__)
#else
#define TRACK_NEW
#endif
#else
#define TRACK_NEW
#endif

#ifdef USE_CUSTOM_ALLOCATE
#ifndef _alloc
#define _alloc(_Size) Engine::HeapManager::s_pDefalutHeapManager->Alloc(_Size)
#endif // !_alloc

#ifndef _aligned_alloc
#define _aligned_alloc(_Size, _Alignment) Engine::HeapManager::s_pDefalutHeapManager->Alloc(_Size, _Alignment)
#endif // !aligned_alloc

#ifndef _free
#define _free(_Ptr) Engine::HeapManager::s_pDefalutHeapManager->Free(_Ptr)
#endif // !_free

#ifndef _aligned_free
#define _aligned_free Engine::HeapManager::s_pDefalutHeapManager->Free(_Ptr)
#endif // !_aligned_free

// standard allocators
void * operator new(size_t i_size);
void operator delete(void * i_ptr);

// tracking allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line);
void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line);

// Allocating from different heaps
void * operator new(size_t i_size, HeapManager * pHeapMananger);
void   operator delete(void * i_ptr, HeapManager * pHeapManager);

#endif

