#pragma once
#include "SmartPtr.h"
#include "ReferenceCounter.h"
namespace Engine
{
	namespace DataSharing
	{
		struct ReferenceCounter;

		template<class T>
		class SmartPtr;

		template<class T>
		class WeakPtr
		{
		private:
			T * m_ptr;
			ReferenceCounter * m_pRefCounter;
		};
	}
}