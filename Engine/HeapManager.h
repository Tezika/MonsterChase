#pragma once

namespace Engine
{
	struct BlockDescriptor
	{
		
		void* m_pBlockSAtartAddr; // pointer to the block of memory this BlockDescriptor describes
		size_t m_sizeBlock; // size of that block of memory
	};
	class HeapManager
	{
	public:
		HeapManager();
		~HeapManager();
		void* Alloc(size_t i_size);
		void* Alloc(size_t i_size, unsigned int i_aligment);
		bool Free(void* i_ptr);
		void Destroy();
	};

}
