#include "pch.h"
#include "BitArray.h"
#include "FixedSizeAllocator.h"
#include "Assert.h"
#include <cstring>
#include <intrin.h>

#pragma intrinsic(_BitScanForward) 

BitArray * BitArray::Create(size_t i_numBits, FixedSizeAllocator * i_pAllocator, bool i_startClear)
{
	return new BitArray(i_numBits, i_startClear);
}

BitArray::BitArray(size_t i_numBits, bool i_clearAll)
{
	size_t i_bitsPerUnit = 64;
	m_sizeOfUnits = i_numBits / i_bitsPerUnit;
	m_pBits = new uint64_t[m_sizeOfUnits];
	assert(m_pBits);
	memset(m_pBits, i_clearAll ? 0 : 1, m_sizeOfUnits);
}

BitArray::BitArray(const BitArray & i_other)
{
	m_sizeOfUnits = i_other.GetUnitSize();
	if (m_pBits != nullptr)
	{
		delete m_pBits;
		m_pBits = nullptr;
	}
	m_pBits = new uint64_t[m_sizeOfUnits];
	assert(m_pBits);
	memcpy_s(m_pBits, GetUnitSize(), i_other.m_pBits, i_other.GetUnitSize());
}

BitArray & BitArray::operator=(const BitArray & i_other)
{
	m_sizeOfUnits = i_other.GetUnitSize();
	if (m_pBits != nullptr)
	{
		delete m_pBits;
		m_pBits = nullptr;
	}
	m_pBits = new uint64_t[m_sizeOfUnits];
	assert(m_pBits);
	memcpy_s(m_pBits, GetUnitSize(), i_other.m_pBits, i_other.GetUnitSize());
	return *this;
}

BitArray::~BitArray()
{
	assert(!this->AreAllClear());
	if (m_pBits != nullptr)
	{
		delete m_pBits;
		m_pBits = nullptr;
	}
}

void BitArray::SetAll()
{
	for (size_t i = 0; i < m_sizeOfUnits; i++)
	{
		m_pBits[i] = ~(m_pBits[i] & 0);
	}
}

void BitArray::ClearAll()
{
	for (size_t i = 0; i < m_sizeOfUnits; i++)
	{
		m_pBits[i] = m_pBits[i] & 0;
	}
}

bool BitArray::AreAllClear() const
{
	size_t bitNumber = -1;
	return !this->GetFirstSetBit(bitNumber);
}

bool BitArray::AreAllSet() const
{
	size_t bitNumber = -1;
	return !this->GetFirstClearBit(bitNumber);
}

void BitArray::SetBit(size_t i_bitNumber)
{
	size_t bit = i_bitNumber % m_sizeOfUnits;
	uint64_t byte = m_pBits[i_bitNumber / m_sizeOfUnits];
	byte = byte | (1 << bit);
	m_pBits[i_bitNumber / m_sizeOfUnits] = byte;
}

void BitArray::ClearBit(size_t i_bitNumber)
{
	size_t bit = i_bitNumber % m_sizeOfUnits;
	uint64_t byte = m_pBits[i_bitNumber / m_sizeOfUnits];
	byte = byte & ~(1 << bit);
	m_pBits[i_bitNumber / m_sizeOfUnits] = byte;
}

bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
{
	size_t cacheBitNumer = o_bitNumber;
	size_t unitIndex = 0;
	size_t bitIndex = 0;
	for (size_t i = 0; i < m_sizeOfUnits; i++)
	{
		uint64_t byte = m_pBits[i];
		for (size_t bit = 0; bit < 64; bit++)
		{
			if ((byte >> bit) & 1 == 0x00)
			{
				unitIndex = i;
				bitIndex = bit;
				break;
			}
		}
	}
	o_bitNumber = unitIndex * 64 + bitIndex;
	return o_bitNumber != cacheBitNumer;
}

bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
{
	size_t cacheBitNumer = o_bitNumber;
	size_t unitIndex = 0;
	// quick skip bytes where no bits are set   
	while ((m_pBits[unitIndex] == 0x00) && (unitIndex < m_sizeOfUnits))
		unitIndex++;
	// use the compiler intrinsics function to find the first set bit.
	unsigned long byte = m_pBits[unitIndex];
	unsigned long bitIndex;
	_BitScanForward(&bitIndex, byte);
	o_bitNumber = unitIndex * 64 + bitIndex;
	return o_bitNumber != cacheBitNumer;
}

bool BitArray::operator[](size_t i_index) const
{
	return m_pBits[i_index] == 0x00;
}
