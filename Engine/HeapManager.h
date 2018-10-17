#pragma once
#include "TList.h"

namespace Engine
{
	struct BlockDescriptor
	{
	public:
		void* m_pBlockSAtartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
		BlockDescriptor* next; //the pointer to the next blockdescriptor
		~BlockDescriptor() { if (m_pBlockSAtartAddr != nullptr) delete m_pBlockSAtartAddr; }
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
		bool Contains(void*) const;
		void Collect();
		bool Free(void*);
		void Destroy();

		size_t GetUsedMemory() { return i_usedMemory_; }
		size_t GetLeftMemory() { return i_sizeOfMemory_ - i_usedMemory_; }

	private:
		void* pMemory_;
		BlockDescriptor* pDescriptorHead_;
		size_t i_sizeOfMemory_;
		size_t i_numOfDescription_;

		//Using for debuging
		size_t i_usedMemory_;

		//Initialized function
		void Initialize();
	};
}
