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
	i_test_ = 0;
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
	if (i_size > this->GetLeftMemory())
	{
		return nullptr;
	}

	//Get one descriptor from the free list firstly
	auto p = pFreeHead_;
	BlockDescriptor* pPrevious = nullptr;
	while (p != nullptr)
	{
		if (p->m_sizeBlock - i_size <= sizeof(BlockDescriptor))
		{

			BlockDescriptor* temp = nullptr;
			//Remove current node from the free list
			if (pPrevious == nullptr)
			{
				temp = pFreeHead_;
				pFreeHead_ = pFreeHead_->m_next;
			}
			else
			{
				temp = p;
				p = p->m_next;
				pPrevious->m_next = p;
			}
			//Add it to the outstanding list
			pOutstandingHead_ = this->InsertNodeToHead(pOutstandingHead_, temp);
			i_usedMemory_ += i_size;
			return temp->m_pBlockStarAddr;
		}
		else if (p->m_sizeBlock - i_size > sizeof(BlockDescriptor))
		{
			//subdivde it into two blocks
			auto originalSize = p->m_sizeBlock;
			auto pBlockAddress = (void*)(static_cast<char*>(p->m_pBlockStarAddr) + originalSize - sizeof(BlockDescriptor) - i_size);
			auto subBlock = static_cast<BlockDescriptor*>(pBlockAddress);
			pBlockAddress = static_cast<char*>(pBlockAddress) + sizeof(BlockDescriptor);
			subBlock->m_sizeBlock = i_size;
			subBlock->m_pBlockStarAddr = subBlock + sizeof(BlockDescriptor);
			
			//change the orginal
			p->m_sizeBlock = originalSize - i_size;
			//add the sub one into the outstanding list;
			pOutstandingHead_ = this->InsertNodeToHead(pOutstandingHead_, subBlock);
			i_usedMemory_ += i_size;
			//DEBUG_PRINT("The current allocation address is 0x%08x and size is %d\n", subBlock->m_pBlockStarAddr, subBlock->m_sizeBlock);
			return subBlock->m_pBlockStarAddr;
		}
		else if (p->m_sizeBlock < i_size)
		{
			pPrevious = p;
			p = p->m_next;
		}
	}

	//Create a descriptor firstly
	BlockDescriptor* pDescriptor = static_cast<BlockDescriptor*>(pMemory_);
	pMemory_ = static_cast<char*>(pMemory_) + sizeof(BlockDescriptor);
	pDescriptor->m_pBlockStarAddr = pMemory_;
	pMemory_ = static_cast<char*>(pMemory_) + i_size;
	pDescriptor->m_sizeBlock = i_size;
	pOutstandingHead_ = this->InsertNodeToHead(pOutstandingHead_, pDescriptor);
	i_usedMemory_ += i_size;
	return pDescriptor->m_pBlockStarAddr;
}

void* Engine::HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool Engine::HeapManager::Free(void* i_ptr)
{
	assert(i_ptr);
	auto p = pOutstandingHead_;
	BlockDescriptor* pPrevious = nullptr;
	while (p != nullptr)
	{
		if (p->m_pBlockStarAddr == i_ptr)
		{
			BlockDescriptor* temp = nullptr;
			//remove the head
			if (pPrevious == nullptr)
			{
				temp = pOutstandingHead_;
				pOutstandingHead_ = pOutstandingHead_->m_next;
			}
			else
			{
				temp = p;
				p = p->m_next;
				pPrevious->m_next = p;
			}
			pFreeHead_ = this->InsertNodeToHead(pFreeHead_, temp);
			i_usedMemory_ -= p->m_sizeBlock;
			break;
		}
		pPrevious = p;
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
	auto p = pOutstandingHead_;
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
	pFreeHead_ = nullptr;
	pOutstandingHead_ = nullptr;
	//update the available using memory for allocator
	i_sizeOfMemory_ = i_sizeOfMemory_ - sizeof(BlockDescriptor) * i_numOfDescription_;
	DEBUG_PRINT("The heapmanager setup successfully.");
}

void Engine::HeapManager::ShowOutstandingAllocations() const
{
	auto p = pOutstandingHead_;
	while (p != nullptr)
	{
		printf("The current allocation address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		DEBUG_PRINT("The current allocation address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		p = p->m_next;
	}
}

void Engine::HeapManager::ShowFreeBlocks() const
{
	auto p = pFreeHead_;
	while (p != nullptr)
	{
		printf("The free blocks' address is 0x%08x and size is %d\n", p->m_pBlockStarAddr, p->m_sizeBlock);
		p = p->m_next;
	}
}

Engine::BlockDescriptor* Engine::HeapManager::InsertNodeToHead(Engine::BlockDescriptor* pHead, Engine::BlockDescriptor* pNode)
{
	pNode->m_next = nullptr;
	if (pHead == nullptr)
	{
		pNode->m_next = nullptr;
		pHead = pNode;
	}
	else
	{
		//Insert the node after the head;
		auto temp = pHead->m_next;
		pHead->m_next = pNode;
		pNode->m_next = temp;
	}
	return pHead;
}


