#include "ReferenceCounter.h"

namespace Engine
{
	ReferenceCounter::ReferenceCounter() :
		weakCount( 0 ),
		refCount( 0 )
	{
	}

	ReferenceCounter::ReferenceCounter( Ref_Counter_t i_weakCount, Ref_Counter_t i_refCount ) :
		weakCount( i_weakCount ),
		refCount( i_refCount )
	{
	}

	ReferenceCounter::ReferenceCounter( const ReferenceCounter & i_other ) :
		refCount( i_other.refCount ),
		weakCount( i_other.weakCount )
	{
	}

	ReferenceCounter & ReferenceCounter::operator=( const ReferenceCounter & i_other )
	{
		refCount = i_other.refCount;
		weakCount = i_other.weakCount;
		return *this;
	}

	ReferenceCounter & ReferenceCounter::operator=( const ReferenceCounter * i_pCounter )
	{
		refCount = i_pCounter->refCount;
		weakCount = i_pCounter->weakCount;
		return *this;
	}
}