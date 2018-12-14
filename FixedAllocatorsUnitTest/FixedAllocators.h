#pragma once

void * __cdecl myMalloc(size_t i_size);
void __cdecl myFree(void * i_ptr);
void * operator new(size_t i_size);
void operator delete(void * i_ptr);
void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);
