#include "stdafx.h"
#include "assert.h"
#include "HeapManager.h"
#include "stdio.h"
#include "string.h"
#include "stddef.h"

size_t Engine::HeapManager::s_MinumumToLeave = 0;

Engine::HeapManager::HeapManager()
{

}

Engine::HeapManager::HeapManager(void* pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
	:m_pMemory_(pMemory), m_sizeOfMemory_(i_sizeMemory), m_numOfDescription_(i_numDescription), m_usedMemory_(0), m_usedDescriptors_(0), m_pDescriptorHead_(nullptr)
{
	DEBUG_PRINT("The heapmanager setup successfully.");
}

Engine::HeapManager::~HeapManager()
{
}

Engine::HeapManager * Engine::HeapManager::Create(void *i_pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
{
	assert(i_pMemory);
	return new HeapManager(i_pMemory, i_sizeMemory, i_numDescription);
}

void Engine::HeapManager::Destroy()
{
	//clear three list data
	DEBUG_PRINT("The heapmanager destroy successfully.");
}

void * Engine::HeapManager::Alloc(size_t i_size)
{
	//If it runs out of the descriptors.
	if (m_usedDescriptors_ > m_numOfDescription_ - 1)
	{
		return nullptr;
	}

	size_t newBlockSize = sizeof(BlockDescriptor) + i_size;
	if (newBlockSize > this->GetLeftMemory() || newBlockSize <= sizeof(BlockDescriptor))
	{
		return nullptr;
	}

	//Get one descriptor from the free list firstly
	auto p = m_pDescriptorHead_;
	while (p != nullptr)
	{
		//if current block has been allocated
		if (p->m_allocated)
		{
			p = this->MoveToNextBlock(p);
			continue;
		}
		//else check the current block.
		//The current block cannot be divided before
		if (p->m_sizeBlock <= newBlockSize)
		{
			m_usedMemory_ += i_size;
			p->m_allocated = true;
			return p->m_pBlockStarAddr;
		}
		//The current block can be divided into two. 
		else if (p->m_sizeBlock > newBlockSize)
		{
			//subdivde it into two blocks
			auto originalSize = p->m_sizeBlock;

			auto pBlockAddress = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(p->m_pBlockStarAddr) + originalSize - newBlockSize);
			auto subBlock = reinterpret_cast<BlockDescriptor *>(pBlockAddress);
			pBlockAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(pBlockAddress) + sizeof(BlockDescriptor));
			subBlock->m_pBlockStarAddr = pBlockAddress;
			pBlockAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(pBlockAddress) + i_size);
			subBlock->m_sizeBlock = i_size;

			//change the orginal
			p->m_sizeBlock = originalSize - newBlockSize;


			m_usedMemory_ += newBlockSize;
			m_usedDescriptors_++;
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
	BlockDescriptor* pDescriptor = reinterpret_cast<BlockDescriptor*>(m_pMemory_);
	m_pMemory_ = reinterpret_cast<char*>(m_pMemory_) + sizeof(BlockDescriptor);
	pDescriptor->m_pBlockStarAddr = m_pMemory_;
	m_pMemory_ = reinterpret_cast<char*>(m_pMemory_) + i_size;
	pDescriptor->m_sizeBlock = i_size;

	m_usedMemory_ += newBlockSize;
	m_usedDescriptors_++;

	pDescriptor->m_allocated = true;
	//check the head
	if (m_pDescriptorHead_ == nullptr)
	{
		m_pDescriptorHead_ = pDescriptor;
	}
	return pDescriptor->m_pBlockStarAddr;
}

void * Engine::HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
{

	return nullptr;
}

bool Engine::HeapManager::Free(void *i_ptr)
{
	assert(i_ptr);
	auto p = m_pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_pBlockStarAddr == i_ptr)
		{
			p->m_allocated = false;
			m_usedMemory_ -= (p->m_sizeBlock + sizeof(BlockDescriptor));
			break;
		}
		p = this->MoveToNextBlock(p);
	}
	return true;
}

bool Engine::HeapManager::Contains(void *i_ptr) const
{
	assert(i_ptr);
	return true;
}

void Engine::HeapManager::Collect()
{
	if (m_pDescriptorHead_ == nullptr)
	{
		return;
	}
	BlockDescriptor* ptr_1 = m_pDescriptorHead_;
	BlockDescriptor* ptr_2 = this->MoveToNextBlock(m_pDescriptorHead_);
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

bool Engine::HeapManager::IsAllocated(void *i_ptr) const
{
	assert(i_ptr);
	auto p = m_pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_pBlockStarAddr == i_ptr)
		{
			return true;
		}
		p = this->MoveToNextBlock(p);
	}
	return false;
}

void Engine::HeapManager::ShowOutstandingAllocations() const
{
	auto p = m_pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_allocated == true)
		{
			printf("The current allocation address is 0x%p and size is %zu\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		}
		p = this->MoveToNextBlock(p);
	}
}

void Engine::HeapManager::ShowFreeBlocks() const
{
	auto p = m_pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_allocated == false)
		{
			printf("The free block's address is 0x%p and size is %zu\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		}
		p = this->MoveToNextBlock(p);
	}
}

void Engine::HeapManager::Combine(Engine::BlockDescriptor *block_1, Engine::BlockDescriptor *block_2)
{
	assert(block_1);
	assert(block_2);
	block_1->m_sizeBlock += (sizeof(BlockDescriptor) + block_2->m_sizeBlock);
	m_usedDescriptors_--;
}

Engine::BlockDescriptor * Engine::HeapManager::MoveToNextBlock(Engine::BlockDescriptor *block) const
{
	assert(block);
	//Move the pointer based on the blocksize.
	auto pNext = reinterpret_cast<BlockDescriptor *>(reinterpret_cast<uintptr_t>(block->m_pBlockStarAddr) + block->m_sizeBlock);
	if (pNext == nullptr || pNext->m_pBlockStarAddr == nullptr)
	{
		return nullptr;
	}
	return pNext;
}

size_t Engine::HeapManager::GetMaxiumAllocatableMemory() const
{
	size_t maxiumFreeMemory = 0;
	BlockDescriptor* p = m_pDescriptorHead_;
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
