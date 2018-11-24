
//Use this file to override the global new & delete
#pragma once
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
