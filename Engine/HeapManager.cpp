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
	if (i_size > this->GetLeftMemory())
	{
		return nullptr;
	}

	//Create a descriptor firstly
	BlockDescriptor* pDescriptor = static_cast<BlockDescriptor*>(pMemory_);
	pMemory_ = static_cast<char*>(pMemory_) + sizeof(BlockDescriptor);
	pDescriptor->m_pBlockSAtartAddr = pMemory_;
	pMemory_ = static_cast<char*>(pMemory_) + i_size;
	pDescriptor->m_sizeBlock = i_size;
	pOutstandingHead_ = this->InsertNodeToHead(pOutstandingHead_, pDescriptor);
	return pDescriptor->m_pBlockSAtartAddr;
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
		if (p->m_pBlockSAtartAddr == i_ptr)
		{
			BlockDescriptor* temp = nullptr;
			//remove the head
			if (pPrevious == nullptr)
			{
				temp = pOutstandingHead_;
				pOutstandingHead_ = pOutstandingHead_->next;
			}
			else
			{
				temp = p;
				p = p->next;
				pPrevious->next = p;
			}
			pFreeHead_ = this->InsertNodeToHead(pFreeHead_, temp);
			break;
		}
		pPrevious = p;
		p = p->next;
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
		if (p->m_pBlockSAtartAddr == i_ptr)
		{
			return true;
		}
		p = p->next;
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
	while (p !=  nullptr)
	{
		printf("The current allocation address is 0x%08x and size is %d\n", p->m_pBlockSAtartAddr, p->m_sizeBlock);
		p = p->next;
	}
}

void Engine::HeapManager::ShowFreeBlocks() const
{
	auto p = pFreeHead_;
	while (p != nullptr)
	{
		printf("The current address is 0x%08x and size is %d", p->m_pBlockSAtartAddr, p->m_sizeBlock);
		p = p->next;
	}
}

Engine::BlockDescriptor* Engine::HeapManager::InsertNodeToHead(Engine::BlockDescriptor* pHead, Engine::BlockDescriptor* pNode)
{
	if (pHead == nullptr)
	{
		pNode->next = nullptr;
		pHead = pNode;
	}
	else
	{
		//Insert the node after the head;
		auto temp = pHead->next;
		pHead->next = pNode;
		pNode->next = temp;
	}
	return pHead;
}


