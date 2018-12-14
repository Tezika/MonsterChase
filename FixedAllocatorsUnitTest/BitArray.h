#pragma once
#include <inttypes.h>

namespace Engine
{
	class HeapManager;

	class BitArray
	{
	public:
		static BitArray * Create(size_t i_numBits, HeapManager * i_pDefaultHeap, bool i_clearAll = true);
		~BitArray();

		void ClearAll(void);
		void SetAll(void);

		bool AreAllClear(void) const;
		bool AreAllSet(void) const;

		inline bool IsBitSet(size_t i_bitNumber) const { return (m_pBits[i_bitNumber / 8] & (1U << (i_bitNumber % 8))); };
		inline bool IsBitClear(size_t i_bitNumber) const { return !this->IsBitSet(i_bitNumber); };

		inline size_t GetByteSize() const { return m_sizeOfBytes; }

		void SetBit(size_t i_bitNumber);
		void ClearBit(size_t i_bitNumber);

		bool GetFirstClearBit(size_t & o_bitNumber) const;
		bool GetFirstSetBit(size_t & o_bitNumber) const;

		bool IsBitValid(size_t i_bitNumber) const;

		bool operator[](size_t i_index) const;

	private:
		//Private it's constructor, copy constructor and assignment operator to make it that can be created by 'Create' method
		BitArray() {};
		BitArray(size_t i_numBits, bool i_clearAll) {};
		BitArray(const BitArray &) {};
		BitArray & operator=(const BitArray &) {};

		uint8_t * m_pBits;
		size_t m_sizeOfBytes;
		size_t m_numOfBits;
	};
}
