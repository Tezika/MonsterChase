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
	auto newSize = sizeof(BlockDescriptor) + i_size;
	if (newSize > this->GetLeftMemory() || newSize == sizeof(BlockDescriptor))
	{
		return nullptr;
	}


	//Get one descriptor from the free list firstly
	auto p = pDescriptorHead_;
	while (p != nullptr)
	{
		//if current block has been allocated
		if (p->m_allocated)
		{
			p = p->m_next;
			continue;
		}
		//else check the current block.
		//The current block cannot be divided before
		if (p->m_sizeBlock <= newSize)
		{
			i_usedMemory_ += i_size;
			p->m_allocated = true;
			return p->m_pBlockStarAddr;
		}
		//The current block can be divided into two. 
		else if (p->m_sizeBlock > newSize)
		{
			//subdivde it into two blocks
			auto originalSize = p->m_sizeBlock;

			auto pBlockAddress = (void*)(static_cast<char*>(p->m_pBlockStarAddr) + originalSize - newSize);
			auto subBlock = static_cast<BlockDescriptor*>(pBlockAddress);
			pBlockAddress = static_cast<char*>(pBlockAddress) + sizeof(BlockDescriptor);
			subBlock->m_pBlockStarAddr = pBlockAddress;
			pBlockAddress = static_cast<char*>(pBlockAddress) + i_size;
			subBlock->m_sizeBlock = i_size;
			subBlock->m_next = nullptr;

			//change the orginal
			p->m_sizeBlock = originalSize - newSize;

			i_usedMemory_ += newSize;
			subBlock->m_allocated = true;
			//add the subBlock to the list
			//Add this descitor to the list tail
			this->InsertNodeToTail(subBlock);
			DEBUG_PRINT("The current allocation address is 0x%08x and size is %d\n", subBlock->m_pBlockStarAddr, subBlock->m_sizeBlock);
			return subBlock->m_pBlockStarAddr;
		}
		else if (p->m_sizeBlock < i_size)
		{
			p = p->m_next;
		}
	}

	//Create a descriptor firstly
	BlockDescriptor* pDescriptor = static_cast<BlockDescriptor*>(pMemory_);
	pMemory_ = static_cast<char*>(pMemory_) + sizeof(BlockDescriptor);
	pDescriptor->m_pBlockStarAddr = pMemory_;
	pMemory_ = static_cast<char*>(pMemory_) + i_size;
	pDescriptor->m_sizeBlock = i_size;
	pDescriptor->m_next = nullptr;
	i_usedMemory_ += (i_size + sizeof(BlockDescriptor));
	pDescriptor->m_allocated = true;
	//Add this descitor to the list
	this->InsertNodeToTail(pDescriptor);
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
			i_usedMemory_ -= p->m_sizeBlock;
			break;
		}
		p = p->m_next;
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
		p = p->m_next;
	}
	return false;
}

void Engine::HeapManager::Initialize()
{
	pDescriptorHead_ = nullptr;
	pDescriptorTail_ = nullptr;
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
		p = p->m_next;
	}
}

void Engine::HeapManager::ShowFreeBlocks() const
{
	auto p = pDescriptorHead_;
	while (p != nullptr)
	{
		if (p->m_allocated == false)
		{
			printf("The free blocks' address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		}
		p = p->m_next;
	}
}

void Engine::HeapManager::InsertNodeToTail(Engine::BlockDescriptor* pDescriptor)
{
	if (pDescriptorHead_ == nullptr && pDescriptorTail_ == nullptr)
	{
		pDescriptorHead_ = pDescriptor;
		pDescriptorTail_ = pDescriptor;
	}
	else
	{
		pDescriptorTail_->m_next = pDescriptor;
		pDescriptorTail_ = pDescriptor;
	}
}
