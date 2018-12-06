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

	//The HeapManager should be a singleton which can be accessed globally.
	class HeapManager
	{
	public:
		static HeapManager * s_pDefalutHeapManager;
		static HeapManager * Create(void *, size_t, unsigned int);
		static size_t s_MinumumToLeave;

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

		inline bool Contains(void * i_ptr) const { return (i_ptr >= m_pMemoryMark) && (i_ptr <= m_pMemoryMark + m_sizeOfMemory); }
		inline size_t GetUsedMemory() const { return m_usedMemory; }
		inline size_t GetLeftMemory() const { return m_sizeOfMemory - m_usedMemory; }
		inline void * GetAssociateMemory() { return m_pMemory; }

	private:
		HeapManager();
		HeapManager(void *, size_t, unsigned int);
		// prevent copy and assignment
		HeapManager(const HeapManager & i_other);
		HeapManager & operator=(const HeapManager & i_other);

		uint8_t * m_pMemory;
		uint8_t * m_pAllocatableMemory;
		uint8_t * m_pMemoryMark;
		BlockDescriptor * m_pDescriptorHead;
		size_t m_sizeOfMemory;
		size_t m_numOfDescription;

		//Using for debuging
		size_t m_usedMemory;
		size_t m_usedDescriptors;

		//Initialized function
		void Combine(BlockDescriptor *, BlockDescriptor *);
		Engine::BlockDescriptor* MoveToNextBlock(Engine::BlockDescriptor *) const;
	};
}
