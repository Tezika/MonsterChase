#pragma once
#include "ConsolePrint.h"
#include "stdint.h"

namespace Engine
{
	struct BlockDescriptor
	{
	public:
		uint8_t * m_pBlockStarAddr; // pointer to the block of memory this BlockDescriptor describes.
		size_t m_sizeBlock; // size of that block of memory
		bool m_allocated; // to flag this block that has been allocated or not.
	};

	class HeapManager
	{
	public:
		static HeapManager * Create(void *, size_t, unsigned int);
		static size_t s_MinumumToLeave;

		HeapManager();
		HeapManager(void *, size_t, unsigned int);
		~HeapManager();
		void * Alloc(size_t);
		void * Alloc(size_t, unsigned int);

		void Collect();
		bool Free(void *);
		void Destroy();

		size_t GetMaxiumAllocatableMemory() const;

		bool IsAllocated(void *) const;
		void ShowFreeBlocks() const;
		void ShowOutstandingAllocations() const;

		inline bool Contains(void * ptr) const { return (ptr >= m_pMemoryStart_) && (ptr <= m_pMemoryStart_ + m_sizeOfMemory_); }
		inline size_t GetUsedMemory() const { return m_usedMemory_; }
		inline size_t GetLeftMemory() const { return m_sizeOfMemory_ - m_usedMemory_; }

	private:
		uint8_t * m_pMemory_;
		uint8_t *  m_pMemoryStart_;
		BlockDescriptor * m_pDescriptorHead_;
		size_t m_sizeOfMemory_;
		size_t m_numOfDescription_;

		//Using for debuging
		size_t m_usedMemory_;
		size_t m_usedDescriptors_;

		//Initialized function
		void Combine(BlockDescriptor *, BlockDescriptor *);
		Engine::BlockDescriptor* MoveToNextBlock(Engine::BlockDescriptor *) const;
	};
}
