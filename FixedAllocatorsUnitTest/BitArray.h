#pragma once
#include <inttypes.h>
class FixedSizeAllocator;

class BitArray
{
public:
	static BitArray * Create(size_t i_numBits, FixedSizeAllocator * i_pAllocator, bool i_startClear = true);
	BitArray(size_t i_numBits, bool i_clearAll);
	BitArray(const BitArray &);
	BitArray & operator=(const BitArray &);
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

	bool operator[](size_t i_index) const;
private:
	BitArray();
	uint8_t * m_pBits;
	size_t m_sizeOfBytes;
	size_t m_numOfBits;
};