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
}

void* Engine::HeapManager::Alloc(size_t i_size)
{
	//Find an apporiate block
	for (size_t i = 0; i < pFreeMemoryList_->Length(); i++)
	{
		
	}
	return nullptr;
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
	pDescriptor_ = static_cast<char*>(pDescriptor_) + sizeof(BlockDescriptor) * i_numOfDescription_;
	this->InitializeDescriptors(64);
	DEBUG_PRINT("The heapmanager initiaized successfully.");
}

void Engine::HeapManager::InitializeDescriptors(size_t size)
{
	//Create the new block descriptors
	for (size_t i = 0; i < i_numOfDescription_; i++)
	{
		//Setup a block
		BlockDescriptor* pBlock = static_cast<BlockDescriptor*>(pDescriptor_);
		pDescriptor_ = static_cast<char*>(pDescriptor_) + sizeof(void*);
		pBlock->m_pBlockSAtartAddr = pMemory_;
		pDescriptor_ = static_cast<char*>(pDescriptor_) + sizeof(size_t);
		pBlock->m_sizeBlock = size;
		pMemory_ = static_cast<char*>(pMemory_) + size;
		pFreeDesciptorList_->InsertToTail(pBlock);
	}
	DEBUG_PRINT("The free descriptorlist lenght is %d", pFreeDesciptorList_->Length());
}

