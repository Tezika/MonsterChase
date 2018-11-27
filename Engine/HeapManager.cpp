#include "stdafx.h"
#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stddef.h"
#include "stdint.h"
#include "HeapManager.h"
#include "Allocator.h"

size_t Engine::HeapManager::s_MinumumToLeave = 0;
Engine::HeapManager * Engine::HeapManager::s_pHeapManager = nullptr;

namespace Engine
{
	HeapManager::HeapManager()
	{

	}

	HeapManager::HeapManager(void *i_pMemory, size_t i_sizeMemory, unsigned int i_numDescription) :
		m_pAllocatableMemory(reinterpret_cast<uint8_t *>(i_pMemory)),
		m_sizeOfMemory(i_sizeMemory),
		m_numOfDescription(i_numDescription),
		m_usedMemory(0),
		m_usedDescriptors(0),
		m_pDescriptorHead(nullptr),
		m_pMemoryMark(reinterpret_cast<uint8_t *>(i_pMemory))
	{

	}

	HeapManager::~HeapManager()
	{

	}

	HeapManager * HeapManager::Create(void *i_pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
	{
		assert(i_pMemory);
		//Create a HeapManager without using custom new
		HeapManager * pHeapManager = reinterpret_cast<HeapManager *>(i_pMemory);

		pHeapManager->m_pMemory = reinterpret_cast<uint8_t *>(i_pMemory);
		pHeapManager->m_pAllocatableMemory = reinterpret_cast<uint8_t *>(i_pMemory) + sizeof(HeapManager);
		pHeapManager->m_pMemoryMark = reinterpret_cast<uint8_t *>(i_pMemory) + sizeof(HeapManager);

		pHeapManager->m_sizeOfMemory = i_sizeMemory - sizeof(HeapManager);
		pHeapManager->m_numOfDescription = i_numDescription;
		pHeapManager->m_usedMemory = 0;
		pHeapManager->m_usedDescriptors = 0;
		pHeapManager->m_pDescriptorHead = nullptr;

		DEBUG_PRINT("The heapmanager setup successfully.");
		return pHeapManager;
	}

	void HeapManager::Destroy()
	{
		DEBUG_PRINT("The heapmanager destroied successfully.");
	}

	void * HeapManager::Alloc(size_t i_size)
	{
		//If it runs out of the descriptors.
		if (m_usedDescriptors > m_numOfDescription - 1)
		{
			return nullptr;
		}

		size_t newBlockSize = sizeof(BlockDescriptor) + i_size;
		if (newBlockSize > this->GetLeftMemory() || newBlockSize <= sizeof(BlockDescriptor))
		{
			return nullptr;
		}

		//Get one descriptor from the free list firstly
		auto p = m_pDescriptorHead;
		while (p != nullptr)
		{
			//if current block has been allocated
			if (p->m_allocated || p->m_sizeBlock < newBlockSize)
			{
				p = this->MoveToNextBlock(p);
				continue;
			}
			//else check the current block.
			//The current block cannot be divided and the size equal the new block.
			if (p->m_sizeBlock == newBlockSize)
			{
				m_usedMemory += i_size;
				p->m_allocated = true;
				return p->m_pBlockStarAddr;
			}
			//The current block can be divided into two. 
			else if (p->m_sizeBlock > newBlockSize)
			{
				//subdivde it into two blocks
				auto originalSize = p->m_sizeBlock;

				auto pBlockAddress = reinterpret_cast<void*>(p->m_pBlockStarAddr + originalSize - newBlockSize);
				auto subBlock = reinterpret_cast<BlockDescriptor *>(pBlockAddress);
				pBlockAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(pBlockAddress) + sizeof(BlockDescriptor));
				subBlock->m_pBlockStarAddr = reinterpret_cast<uint8_t *>(pBlockAddress);
				pBlockAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(pBlockAddress) + i_size);
				subBlock->m_sizeBlock = i_size;

				//change the orginal
				p->m_sizeBlock = originalSize - newBlockSize;


				m_usedMemory += newBlockSize;
				m_usedDescriptors++;
				subBlock->m_allocated = true;
				//add the subBlock to the list
				//DEBUG_PRINT("The current allocation address is 0x%08x and size is %d\n", subBlock->m_pBlockStarAddr, subBlock->m_sizeBlock);
				return subBlock->m_pBlockStarAddr;
			}
			else if (p->m_sizeBlock < i_size)
			{
				p = this->MoveToNextBlock(p);
			}
		}

		//Create a descriptor firstly
		BlockDescriptor* pDescriptor = reinterpret_cast<BlockDescriptor *>(m_pAllocatableMemory);
		m_pAllocatableMemory = m_pAllocatableMemory + sizeof(BlockDescriptor);
		pDescriptor->m_pBlockStarAddr = reinterpret_cast<uint8_t *>(m_pAllocatableMemory);
		m_pAllocatableMemory = m_pAllocatableMemory + i_size;
		pDescriptor->m_sizeBlock = i_size;

		m_usedMemory += newBlockSize;
		m_usedDescriptors++;

		pDescriptor->m_allocated = true;
		//check the head
		if (m_pDescriptorHead == nullptr)
		{
			m_pDescriptorHead = pDescriptor;
		}
		return pDescriptor->m_pBlockStarAddr;
	}

	void * HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
	{
		//The Aligment alloc will come soon.
		return Alloc(i_size);
	}

	bool HeapManager::Free(void *i_ptr)
	{
		assert(i_ptr);
		auto p = m_pDescriptorHead;
		while (p != nullptr)
		{
			if (p->m_pBlockStarAddr == i_ptr)
			{
				p->m_allocated = false;
				m_usedMemory -= (p->m_sizeBlock + sizeof(BlockDescriptor));
				break;
			}
			p = this->MoveToNextBlock(p);
		}
		return true;
	}


	void HeapManager::Collect()
	{
		if (m_pDescriptorHead == nullptr)
		{
			return;
		}
		BlockDescriptor* ptr_1 = m_pDescriptorHead;
		BlockDescriptor* ptr_2 = this->MoveToNextBlock(m_pDescriptorHead);
		while (ptr_2 != nullptr)
		{
			//Can be combined.
			if (!ptr_1->m_allocated && !ptr_2->m_allocated)
			{
				auto temp = ptr_2;
				ptr_2 = this->MoveToNextBlock(ptr_2);
				this->Combine(ptr_1, temp);
			}
			//Cannot be combined right now.
			else
			{
				while (ptr_2 != nullptr && ptr_2->m_allocated)
				{
					ptr_2 = this->MoveToNextBlock(ptr_2);
				}
				//no free block now
				if (ptr_2 == nullptr)
				{
					break;
				}
				ptr_1 = ptr_2;
				ptr_2 = this->MoveToNextBlock(ptr_2);
			}
		}
	}

	bool HeapManager::IsAllocated(void *i_ptr) const
	{
		assert(i_ptr);
		return reinterpret_cast<BlockDescriptor*>((reinterpret_cast<uint8_t *>(i_ptr) - sizeof(BlockDescriptor))) != nullptr ? true : false;
	}

	void HeapManager::ShowOutstandingAllocations() const
	{
		auto p = m_pDescriptorHead;
		while (p != nullptr)
		{
			if (p->m_allocated == true)
			{
				printf("The current allocation address is 0x%p and size is %zu\n", reinterpret_cast<uint8_t *>(p->m_pBlockStarAddr), p->m_sizeBlock);
			}
			p = this->MoveToNextBlock(p);
		}
	}

	void HeapManager::ShowFreeBlocks() const
	{
		auto p = m_pDescriptorHead;
		while (p != nullptr)
		{
			if (p->m_allocated == false)
			{
				printf("The free block's address is 0x%p and size is %zu\n", reinterpret_cast<uint8_t *>(p->m_pBlockStarAddr), p->m_sizeBlock);
			}
			p = this->MoveToNextBlock(p);
		}
	}

	void HeapManager::Combine(BlockDescriptor *i_pBlock_1, BlockDescriptor *i_pBlock_2)
	{
		assert(i_pBlock_1);
		assert(i_pBlock_2);
		i_pBlock_1->m_sizeBlock += (sizeof(BlockDescriptor) + i_pBlock_2->m_sizeBlock);
		m_usedDescriptors--;
	}

	BlockDescriptor * HeapManager::MoveToNextBlock(BlockDescriptor *i_pBlock) const
	{
		assert(i_pBlock);
		//Move the pointer based on the blocksize.
		auto pNext = reinterpret_cast<BlockDescriptor *>(i_pBlock->m_pBlockStarAddr + i_pBlock->m_sizeBlock);
		if (pNext == nullptr || pNext->m_pBlockStarAddr == nullptr)
		{
			return nullptr;
		}
		return pNext;
	}

	size_t HeapManager::GetMaxiumAllocatableMemory() const
	{
		size_t maxiumFreeMemory = 0;
		BlockDescriptor* p = m_pDescriptorHead;
		while (p != nullptr)
		{
			if (!p->m_allocated)
			{
				if (p->m_sizeBlock > maxiumFreeMemory)
				{
					maxiumFreeMemory = p->m_sizeBlock;
				}
			}
			p = this->MoveToNextBlock(p);
		}
		maxiumFreeMemory = maxiumFreeMemory > (this->GetLeftMemory() - sizeof(BlockDescriptor)) ? maxiumFreeMemory : (this->GetLeftMemory() - sizeof(BlockDescriptor));
		return maxiumFreeMemory;
	}
}
