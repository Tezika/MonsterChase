#pragma once

namespace Engine
{
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
