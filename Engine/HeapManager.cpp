#include "stdafx.h"
#include "assert.h"
#include "HeapManager.h"
#include "stdio.h"
#include "string.h"

Engine::HeapManager::HeapManager()
{
}

Engine::HeapManager::HeapManager(void* pMemory, size_t i_sizeMemory, unsigned int i_numDescription)
{
	pFreeDesciptorList_ = new TList<BlockDescriptor>();
	pFreeMemoryList_ = new TList<BlockDescriptor>();
	pOutstandingAllocationList_ = new TList<BlockDescriptor>();
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
	delete pFreeDesciptorList_;
	delete pFreeMemoryList_;
	delete pOutstandingAllocationList_;
	DEBUG_PRINT("The heapmanager destroy successfully.");
}

void* Engine::HeapManager::Alloc(size_t i_size)
{
	//Find an apporiate block
	auto p = pFreeMemoryList_->head;
	void* allocatedMemory = nullptr;
	while (p != nullptr)
	{
		if (p->data->m_sizeBlock > i_size)
		{
			//get a new block descriptor
			auto descriptor = this->GetDescriptorFromPool();
			descriptor->m_pBlockSAtartAddr = p->data->m_pBlockSAtartAddr;
			descriptor->m_sizeBlock = i_size;
			pOutstandingAllocationList_->InsertToTail(descriptor);

			//subdivide current block
			p->data->m_sizeBlock -= i_size;
			p->data->m_pBlockSAtartAddr = static_cast<char*>(p->data->m_pBlockSAtartAddr) + i_size;

			allocatedMemory = descriptor->m_pBlockSAtartAddr;
			i_usedMemory_ += i_size;
			break;
		}
		else if (p->data->m_sizeBlock == i_size)
		{
			allocatedMemory = p->data->m_pBlockSAtartAddr;
			i_usedMemory_ += i_size;
			pFreeMemoryList_->Remove(p);
			pOutstandingAllocationList_->InsertToTail(p->data);
		}
		else
		{
			DEBUG_PRINT("The left memory %d bytes cannot afford the allocation for %d bytes", this->GetLeftMemory(), i_size);
		}
	}
	return allocatedMemory;
}

void* Engine::HeapManager::Alloc(size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool Engine::HeapManager::Free(void* i_ptr)
{
	assert(i_ptr);
	return true;
}

void Engine::HeapManager::Initialize()
{
	pDescriptor_ = pMemory_;
	pDescriptor_ = static_cast<char*>(pDescriptor_) + i_sizeOfMemory_ - sizeof(BlockDescriptor) * i_numOfDescription_;
	this->InitializeDescriptorPool();
	this->InitilaizeFreeMemory();
	DEBUG_PRINT("The heapmanager setup successfully.");
}

void Engine::HeapManager::InitializeDescriptorPool()
{
	//Create the new block descriptors
	for (size_t i = 0; i < i_numOfDescription_; i++)
	{
		//Setup a block
		BlockDescriptor* pBlock = static_cast<BlockDescriptor*>(pDescriptor_);
		pDescriptor_ = static_cast<char*>(pDescriptor_) + sizeof(void*);
		pBlock->m_pBlockSAtartAddr = nullptr;
		pDescriptor_ = static_cast<char*>(pDescriptor_) + sizeof(size_t);
		pBlock->m_sizeBlock = 0;
		pFreeDesciptorList_->InsertToTail(pBlock);
	}
	DEBUG_PRINT("The free descriptor list finished the setup. The free descriptor list length is %d", pFreeDesciptorList_->Length());
}

void Engine::HeapManager::InitilaizeFreeMemory()
{
	auto descriptor = this->GetDescriptorFromPool();
	assert(descriptor != nullptr);
	descriptor->m_pBlockSAtartAddr = pMemory_;
	descriptor->m_sizeBlock = i_sizeOfMemory_ - i_numOfDescription_ * sizeof(BlockDescriptor);
	pFreeMemoryList_->InsertToTail(descriptor);
	DEBUG_PRINT("The free memory list finished the setup.");
}

Engine::BlockDescriptor* Engine::HeapManager::GetDescriptorFromPool()
{
	assert(pFreeDesciptorList_ != nullptr);
	auto descriptor = pFreeDesciptorList_->head->data;
	pFreeDesciptorList_->Remove(pFreeDesciptorList_->head);
	return descriptor;
}
