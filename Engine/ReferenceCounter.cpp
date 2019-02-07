#include "stdafx.h"
#include "ReferenceCounter.h"

namespace Engine
{
	namespace DataSharing
	{
		ReferenceCounter::ReferenceCounter() :
			m_weakReferenceCount( 0 ),
			m_strongReferenceCount( 0 )
		{
		}

		ReferenceCounter::ReferenceCounter( long i_weakCount, long i_strongCount ) :
			m_weakReferenceCount( i_weakCount ),
			m_strongReferenceCount( i_strongCount )
		{
		}

		ReferenceCounter::ReferenceCounter( const ReferenceCounter & i_other ) :
			m_strongReferenceCount( i_other.m_strongReferenceCount ),
			m_weakReferenceCount( i_other.m_weakReferenceCount )
		{

		}

		void ReferenceCounter::operator=( const ReferenceCounter & i_other )
		{
			m_strongReferenceCount = i_other.m_strongReferenceCount;
			m_weakReferenceCount = i_other.m_weakReferenceCount;
		}
	}
}