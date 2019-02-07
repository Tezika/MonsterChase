#pragma once
#include "stdint.h"

namespace Engine
{
	namespace DataSharing
	{
		typedef uint64_t Ref_Counter_t;

		struct ReferenceCounter
		{
			ReferenceCounter();
			ReferenceCounter( Ref_Counter_t, Ref_Counter_t );
			ReferenceCounter( const ReferenceCounter & );
			ReferenceCounter & operator=( const ReferenceCounter & );
			ReferenceCounter & operator= ( const ReferenceCounter * );
			ReferenceCounter & operator++( );

			Ref_Counter_t weakCount;
			Ref_Counter_t refCount;
		};
	}
}