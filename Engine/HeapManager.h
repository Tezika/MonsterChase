#pragma once

#include "TList.h"

namespace Engine
{
	struct BlockDescriptor
	{
	public:
		void* m_pBlockSAtartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* m_pNext; //The next block's pointer
	};

	class HeapManager
	{
	public:
		HeapManager();
		HeapManager(void*, size_t, unsigned int);
		~HeapManager();
		void* Alloc(size_t);
		void* Alloc(size_t, unsigned int);
		static HeapManager* Create(void*, size_t, unsigned int);
		bool Free(void*);
		void Destroy();

	private:
		TList<BlockDescriptor>* pFreeMemoryList_;
		TList<BlockDescriptor>* pOutstandingAllocationList_;
		TList<BlockDescriptor>* pFreeDesciptorList_;

		void* pMemory_;
		void* pDescriptor_;
		size_t i_sizeOfMemory_;
		size_t i_numOfDescription_;

		void Initialize();
		void InitializeDescriptors(size_t);
	};
}
