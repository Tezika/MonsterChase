#pragma once
#include "TList.h"

namespace Engine
{
	struct BlockDescriptor
	{
	public:
		void* m_pBlockSAtartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
	};

	class HeapManager
	{
	public:
		static HeapManager* Create(void*, size_t, unsigned int);

		HeapManager();
		HeapManager(void*, size_t, unsigned int);
		~HeapManager();
		void* Alloc(size_t);
		void* Alloc(size_t, unsigned int);
		bool Free(void*);
		void Destroy();

		size_t GetUsedMemory() { return i_usedMemory_; }
		size_t GetLeftMemory() { return i_sizeOfMemory_ - i_usedMemory_; }

	private:
		TList<BlockDescriptor> *pFreeMemoryList_;
		TList<BlockDescriptor> *pOutstandingAllocationList_;
		TList<BlockDescriptor> *pFreeDesciptorList_;

		void* pMemory_;
		void* pDescriptor_;
		size_t i_sizeOfMemory_;
		size_t i_numOfDescription_;

		//Using for debuging
		size_t i_usedMemory_;

		//Initialized function
		void Initialize();
		void InitilaizeFreeMemory();
		void InitializeDescriptorPool();


		BlockDescriptor* GetDescriptorFromPool();
	};
}
