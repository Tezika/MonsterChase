#pragma once

#include "TList.h"
namespace Engine
{
	struct BlockDescriptor
	{
		void* m_pBlockSAtartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
	};
	class HeapManager
	{

	public:
		HeapManager();
		~HeapManager();
		void* Alloc(size_t );
		void* Alloc(size_t, unsigned int);
		HeapManager* Create(void*, size_t, unsigned int);
		bool Free(void*);
		void Destroy();
	private:
		TList<BlockDescriptor>* pFreeMemoryList_;
		TList<BlockDescriptor>* pOutstandingAllocationList_;
		TList<BlockDescriptor>* pFreeDesciptorList_;
	};

}
