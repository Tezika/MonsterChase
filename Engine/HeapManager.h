#pragma once
#include "ConsolePrint.h"
#include "stdint.h"

namespace Engine
{

#ifndef ALIGNMENT_ALLOCATION
#define ALIGNMENT_ALLOCATION
#endif // ALIGNMENT_ALLOCATION

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
		static HeapManager * Create( void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors );
		static size_t s_MinumumToLeave;
		static unsigned int s_alignment;

		~HeapManager();

		HeapManager( const HeapManager & i_other ) = delete;
		HeapManager & operator=( const HeapManager & i_other ) = delete;
		HeapManager( HeapManager && i_other ) = delete;
		HeapManager &operator=( HeapManager && i_other ) = delete;

		void * Alloc( size_t i_sizeMemory );
		void * Alloc( size_t i_sizeMemory, unsigned int i_alignment );

		void Collect();
		bool Free( void * i_ptr );
		void Destroy();

		size_t GetMaxiumAllocatableMemory() const;

		bool IsAllocated( void * i_ptr ) const;
		void ShowFreeBlocks() const;
		void ShowOutstandingAllocations() const;

		inline bool Contains( void * i_ptr ) const { return (i_ptr >= m_pMemoryMark) && (i_ptr <= m_pMemoryMark + m_sizeOfMemory); }
		inline size_t GetUsedMemory() const { return m_usedMemory; }
		inline size_t GetLeftMemory() const { return m_sizeOfMemory - m_usedMemory; }
		inline void * GetAssociateMemory() { return m_pMemory; }

	private:
		HeapManager();
		HeapManager( void * i_pMemory, size_t i_size, unsigned int i_numDescriptors );

		uint8_t * m_pMemory;
		uint8_t * m_pAllocatableMemory;
		uint8_t * m_pMemoryMark;
		uint8_t * m_pMemoryBoundary;
		BlockDescriptor * m_pDescriptorHead;
		size_t m_sizeOfMemory;
		size_t m_numOfDescription;

		// Using for debuging
		size_t m_usedMemory;
		size_t m_usedDescriptors;

		// Initialization functions
		void Combine( BlockDescriptor * i_pBlock_1, BlockDescriptor * i_pBlock_2 );
		Engine::BlockDescriptor* MoveToNextBlock( Engine::BlockDescriptor * i_pDescriptor ) const;
	};
}
