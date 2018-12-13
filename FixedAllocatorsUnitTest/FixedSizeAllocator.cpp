#include "pch.h"
#include "FixedSizeAllocator.h"
#include "BitArray.h"
#include "Assert.h"

FixedSizeAllocator * FixedSizeAllocator::Create(size_t i_size, size_t i_numOfBlocks)
{
	return new FixedSizeAllocator(i_size, i_numOfBlocks);
}

FixedSizeAllocator::FixedSizeAllocator(size_t i_size, size_t i_numOfBlocks)
	:m_size(i_size),
	m_numOfBlocks(i_numOfBlocks)
{

}

FixedSizeAllocator::FixedSizeAllocator(const FixedSizeAllocator & i_other)
	: m_size(i_other.m_size),
	m_numOfBlocks(i_other.m_numOfBlocks),
	m_pAllocationArray(i_other.m_pAllocationArray)
{
}

FixedSizeAllocator & FixedSizeAllocator::operator=(const FixedSizeAllocator & i_other)
{
	m_size = i_other.m_size;
	m_numOfBlocks = i_other.m_numOfBlocks;
	m_pAllocationArray = i_other.m_pAllocationArray;
}

FixedSizeAllocator::~FixedSizeAllocator()
{
	assert(m_pAllocationArray->AreAllClear());
	delete m_pAllocationArray;
}