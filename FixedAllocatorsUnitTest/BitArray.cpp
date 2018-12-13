#include "pch.h"
#include "BitArray.h"
#include "Assert.h"
#include <cstring>
#include <math.h>
#include <intrin.h>
#include "HeapManager.h"

#pragma intrinsic(_BitScanForward) 

namespace Engine
{
	BitArray * BitArray::Create(size_t i_numBits, HeapManager * i_pDefaultHeap, bool i_clearAll)
	{
		assert(i_pDefaultHeap);
		BitArray * p_bitArray = reinterpret_cast<BitArray *>(i_pDefaultHeap->Alloc(sizeof(BitArray)));
		assert(p_bitArray);

		p_bitArray->m_numOfBits = i_numBits;
		float i_bitsPerUnit = 8;
		p_bitArray->m_sizeOfBytes = (size_t)ceil((float)(i_numBits / i_bitsPerUnit));

		p_bitArray->m_pBits = reinterpret_cast<uint8_t *>(i_pDefaultHeap->Alloc(p_bitArray->m_sizeOfBytes));
		memset(p_bitArray->m_pBits, i_clearAll ? 0 : UINT8_MAX, p_bitArray->m_sizeOfBytes);
		return p_bitArray;
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
		memset(m_pBits, UINT8_MAX, m_sizeOfBytes);
	}

	void BitArray::ClearAll()
	{
		memset(m_pBits, 0, m_sizeOfBytes);
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
		assert(i_bitNumber < m_numOfBits);
		size_t bit = i_bitNumber % 8;
		size_t byteIndex = i_bitNumber / 8;
		uint8_t byte = m_pBits[byteIndex];
		byte |= (1U << bit);
		m_pBits[byteIndex] = byte;
	}

	void BitArray::ClearBit(size_t i_bitNumber)
	{
		assert(i_bitNumber < m_numOfBits);
		size_t bit = i_bitNumber % 8;
		size_t byteIndex = i_bitNumber / 8;
		uint8_t byte = m_pBits[byteIndex];
		byte &= ~(1U << bit);
		m_pBits[byteIndex] = byte;
	}

	bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
	{
		size_t byteIndex = m_sizeOfBytes;
		size_t bitIndex = 0;
		bool foundBit = false;
		for (size_t i = 0; i < m_sizeOfBytes; i++)
		{
			if (m_pBits[i] == UINT8_MAX)
			{
				continue;
			}
			for (size_t bit = 0; bit < 8; bit++)
			{
				if (this->IsBitClear(i * 8 + bit))
				{
					byteIndex = i;
					bitIndex = bit;
					foundBit = true;
					break;
				}
			}
			if (foundBit)
			{
				break;
			}
		}
		o_bitNumber = byteIndex * 8 + bitIndex;
		return o_bitNumber != m_numOfBits;
	}

	bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
	{
		size_t byteIndex = 0;
		// quick skip bytes where no bits are set   
		while ((m_pBits[byteIndex] == 0) && (byteIndex < m_sizeOfBytes))
			byteIndex++;
		if (byteIndex == m_sizeOfBytes)
		{
			return false;
		}
		// use the compiler intrinsics function to find the first set bit.
		unsigned long byte = m_pBits[byteIndex];
		unsigned long bitIndex;
		_BitScanForward(&bitIndex, byte);
		o_bitNumber = byteIndex * 8 + bitIndex;
		return o_bitNumber != m_numOfBits;
	}

	bool BitArray::operator[](size_t i_index) const
	{
		return this->IsBitSet(i_index);
	}

	bool BitArray::IsBitValid(size_t i_bitNumber) const
	{
		return i_bitNumber >= 0 && i_bitNumber < m_numOfBits;
	}
}

