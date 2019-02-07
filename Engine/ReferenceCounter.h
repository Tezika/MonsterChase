#pragma once
namespace Engine
{
	namespace DataSharing
	{
		struct ReferenceCounter
		{
			ReferenceCounter();
			ReferenceCounter( long i_strongCount, long i_weakCount );
			ReferenceCounter( const ReferenceCounter & );
			void operator=( const ReferenceCounter & );

			long m_weakReferenceCount;
			long m_strongReferenceCount;
		};
	}
}