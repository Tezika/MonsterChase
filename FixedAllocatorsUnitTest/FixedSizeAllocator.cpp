#include "pch.h"
#include "FixedSizeAllocator.h"
#include "BitArray.h"
#include "Assert.h"
#include "HeapManager.h"

FixedSizeAllocator * FixedSizeAllocator::Create(size_t i_sizeOfBlock, size_t i_numOfBlocks, void * i_pAllocateMemory)
{
	return new FixedSizeAllocator(i_sizeOfBlock, i_numOfBlocks, i_pAllocateMemory);
}

FixedSizeAllocator::FixedSizeAllocator(size_t i_sizeOfBlock, size_t i_numOfBlocks, void * i_pAllocateMemory)
	:m_sizeOfBlock(i_sizeOfBlock),
	m_numOfBlocks(i_numOfBlocks),
	m_pAllocateMemory(reinterpret_cast<uint8_t *>(i_pAllocateMemory))
{
	//Based on the number of blocks to create a bit array which manages the allocation.
	m_pAllocationBitsArray = BitArray::Create(i_numOfBlocks, false);
}

FixedSizeAllocator::FixedSizeAllocator(const FixedSizeAllocator & i_other)
	:m_sizeOfBlock(i_other.m_sizeOfBlock),
	m_numOfBlocks(i_other.m_numOfBlocks),
	m_pAllocationBitsArray(i_other.m_pAllocationBitsArray)
{
	//Should memory to this new fixed allocator
	m_pAllocationBitsArray->SetAll();
}

FixedSizeAllocator & FixedSizeAllocator::operator=(const FixedSizeAllocator & i_other)
{
	m_sizeOfBlock = i_other.m_sizeOfBlock;
	m_numOfBlocks = i_other.m_numOfBlocks;
	m_pAllocationBitsArray = i_other.m_pAllocationBitsArray;
	m_pAllocationBitsArray->SetAll();
	//Should copy memory to this new fixed allocator
	//m_pAllocateMemory = i_other.m_pAllocateMemory;
	return *this;
}

FixedSizeAllocator::~FixedSizeAllocator()
{
	assert(m_pAllocationBitsArray->AreAllClear());
	delete m_pAllocationBitsArray;
}

void * FixedSizeAllocator::Alloc()
{
	size_t i_firstAvailable;

	if (m_pAllocationBitsArray->GetFirstSetBit(i_firstAvailable))
	{
		// mark it in use because we're going to allocate it to user
		m_pAllocationBitsArray->ClearBit(i_firstAvailable);

		// calculate it’s address and return it to user
		return m_pAllocateMemory + (i_firstAvailable * m_sizeOfBlock);
	}
	else
	{
		return nullptr;
	}
}

bool FixedSizeAllocator::Free(void * i_ptr)
{
	assert(i_ptr != nullptr);
	//calcuate the bit index for allocate memory
	size_t i_clearBitNumber = (reinterpret_cast<uint8_t *>(i_ptr) - m_pAllocateMemory) / m_sizeOfBlock;
	//check if it is the valid index
	if (!m_pAllocationBitsArray ->IsBitValid(i_clearBitNumber))
	{
		return false;
	}
	//check if it's been already set
	if (m_pAllocationBitsArray->IsBitClear(i_clearBitNumber))
	{
		//set this bit.
		m_pAllocationBitsArray->SetBit(i_clearBitNumber);
		return true;
	}
	else
	{
		return false;
	}
}