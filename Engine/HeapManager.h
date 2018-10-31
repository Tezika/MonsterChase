#pragma once
#include "ConsolePrint.h"

namespace Engine
{
	struct BlockDescriptor
	{
	public:
		void * m_pBlockStarAddr; // pointer to the block of memory this BlockDescriptor describes.
		size_t m_sizeBlock; // size of that block of memory
		bool m_allocated; // to flag this block that has been allocated or not.
	};

	class HeapManager
	{
	public:
		static HeapManager* Create(void *, size_t, unsigned int);
		static size_t s_MinumumToLeave;

		HeapManager();
		HeapManager(void *, size_t, unsigned int);
		~HeapManager();
		void * Alloc(size_t);
		void * Alloc(size_t, unsigned int);
		bool Contains(void *) const;
		void Collect();
		bool Free(void *);
		void Destroy();

		inline size_t GetUsedMemory() const { return i_usedMemory_; }
		inline size_t GetLeftMemory() const { return i_sizeOfMemory_ - i_usedMemory_; }
		inline size_t GetMaxiumAllocatedMemory() const { return this->GetLeftMemory() - sizeof(BlockDescriptor); }

		bool IsAllocated(void *) const;
		void ShowFreeBlocks() const;
		void ShowOutstandingAllocations() const;

	private:
		void * m_pMemory_;
		BlockDescriptor * m_pDescriptorHead_;
		size_t i_sizeOfMemory_;
		size_t i_numOfDescription_;

		//Using for debuging
		size_t i_usedMemory_;
		size_t i_usedDescriptors_;

		//Initialized function
		void Combine(BlockDescriptor *, BlockDescriptor *);
		Engine::BlockDescriptor* MoveToNextBlock(Engine::BlockDescriptor *) const;
	};
}
