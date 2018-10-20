#include "stdafx.h"
#include "assert.h"
#include "HeapManager.h"
#include "stdio.h"
#include "string.h"

size_t Engine::HeapManager::s_MinumumToLeave = 0;

Engine::HeapManager::HeapManager()
{

}

Engine::HeapManager::HeapManager(void* pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
{
	pMemory_ = pMemory;
	i_sizeOfMemory_ = i_sizeMemory;
	i_numOfDescription_ = i_numDescription;
	i_usedMemory_ = 0;

	this->Initialize();
}

Engine::HeapManager::~HeapManager()
{
}

Engine::HeapManager* Engine::HeapManager::Create(void* i_pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
{
	assert(i_pMemory);
	return new HeapManager(i_pMemory, i_sizeMemory, i_numDescription);
}

void Engine::HeapManager::Destroy()
{
	//clear three list data
	DEBUG_PRINT("The heapmanager destroy successfully.");
}

void* Engine::HeapManager::Alloc(size_t i_size)
{
	if (i_size > this->GetLeftMemory() || i_size <= 0)
	{
		return nullptr;
	}
	size_t newBlockSize = sizeof(BlockDescriptor) + i_size;

	//Get one descriptor from the free list firstly
	auto p = pDescriptorHead_;
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
			i_usedMemory_ += i_size;
			p->m_allocated = true;
			return p->m_pBlockStarAddr;
		}
		//The current block can be divided into two. 
		else if (p->m_sizeBlock > newBlockSize)
		{
			//subdivde it into two blocks
			auto originalSize = p->m_sizeBlock;

			auto pBlockAddress = (void*)(static_cast<char*>(p->m_pBlockStarAddr) + originalSize - newBlockSize);
			auto subBlock = reinterpret_cast<BlockDescriptor*>(pBlockAddress);
			pBlockAddress = reinterpret_cast<char*>(pBlockAddress) + sizeof(BlockDescriptor);
			subBlock->m_pBlockStarAddr = pBlockAddress;
			pBlockAddress = reinterpret_cast<char*>(pBlockAddress) + i_size;
			subBlock->m_sizeBlock = i_size;

			//change the orginal
			p->m_sizeBlock = originalSize - newBlockSize;

			i_usedMemory_ += newBlockSize;
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
	BlockDescriptor* pDescriptor = reinterpret_cast<BlockDescriptor*>(pMemory_);
	pMemory_ = reinterpret_cast<char*>(pMemory_) + sizeof(BlockDescriptor);
	pDescriptor->m_pBlockStarAddr = pMemory_;
	pMemory_ = reinterpret_cast<char*>(pMemory_) + i_size;
	pDescriptor->m_sizeBlock = i_size;
	i_usedMemory_ += newBlockSize;
	pDescriptor->m_allocated = true;
	//check the head
	if (pDescriptorHead_ == nullptr)
	{
		pDescriptorHead_ = pDescriptor;
	}
	//DEBUG_PRINT("The current allocation address is 0x%08x and size is %d\n", pDescriptor->m_pBlockStarAddr, pDescriptor->m_sizeBlock);
	return pDescriptor->m_pBlockStarAddr;
}

void* Engine::HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool Engine::HeapManager::Free(void* i_ptr)
{
	assert(i_ptr);
	auto p = pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_pBlockStarAddr == i_ptr)
		{
			p->m_allocated = false;
			i_usedMemory_ -= (p->m_sizeBlock + sizeof(BlockDescriptor));
			break;
		}
		p = this->MoveToNextBlock(p);
	}
	return true;
}

bool Engine::HeapManager::Contains(void* i_ptr) const
{
	assert(i_ptr);
	return true;
}

void Engine::HeapManager::Collect()
{
	if (pDescriptorHead_ == nullptr)
	{
		return;
	}
	BlockDescriptor* ptr_1 = pDescriptorHead_;
	BlockDescriptor* ptr_2 = this->MoveToNextBlock(pDescriptorHead_);
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

bool Engine::HeapManager::IsAllocated(void* i_ptr) const
{
	assert(i_ptr);
	auto p = pDescriptorHead_;
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

void Engine::HeapManager::Initialize()
{
	pDescriptorHead_ = nullptr;
	DEBUG_PRINT("The heapmanager setup successfully.");
}

void Engine::HeapManager::ShowOutstandingAllocations() const
{
	auto p = pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_allocated == true)
		{
			printf("The current allocation address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		}
		p = this->MoveToNextBlock(p);
	}
}

void Engine::HeapManager::ShowFreeBlocks() const
{
	auto p = pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_allocated == false)
		{
			printf("The free block's address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		}
		p = this->MoveToNextBlock(p);
	}
}

void Engine::HeapManager::Combine(Engine::BlockDescriptor* block_1, Engine::BlockDescriptor* block_2)
{
	assert(block_1);
	assert(block_2);
	//DEBUG_PRINT("Combine the 0x%08x size %d next is 0x%08x - with - the 0x%08x size %d next is 0x%08x", block_1, block_1->m_sizeBlock, block_1->m_pBlockStarAddr, block_2, block_2->m_sizeBlock, block_2->m_pBlockStarAddr);
	block_1->m_sizeBlock += (sizeof(BlockDescriptor) + block_2->m_sizeBlock);
}

Engine::BlockDescriptor* Engine::HeapManager::MoveToNextBlock(Engine::BlockDescriptor* block) const
{
	assert(block);
	//Move the pointer based on the blocksize.
	auto pNext = reinterpret_cast<BlockDescriptor*>(reinterpret_cast<char*>(block->m_pBlockStarAddr) + block->m_sizeBlock);
	if (pNext == nullptr || pNext->m_pBlockStarAddr == nullptr)
	{
		return nullptr;
	}
	return pNext;
}
