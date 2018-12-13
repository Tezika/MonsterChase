#pragma once
class BitArray;

class FixedSizeAllocator
{
public:
	static FixedSizeAllocator * Create(size_t i_size, size_t i_numOfBlocks);
	FixedSizeAllocator(size_t i_size, size_t i_numOfBlocks);
	FixedSizeAllocator(const FixedSizeAllocator & i_other);
	FixedSizeAllocator & operator=(const FixedSizeAllocator & i_other);
	~FixedSizeAllocator();

	inline const size_t GetSize() { return m_size; }
private:
	FixedSizeAllocator() {};

	size_t m_size;
	size_t m_numOfBlocks;
	BitArray * m_pAllocationArray;
};