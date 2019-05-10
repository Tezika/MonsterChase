#pragma once

#include <assert.h>

namespace Engine
{
	namespace Messaging
	{
		template<typename...Params>
		class Delegate
		{
		public:
			Delegate() :
				m_pInstance( nullptr ),
				m_pMethod( nullptr )
			{
			}

			template<typename T, void ( T::*TMethod )( Params ... )>
			static Delegate Create( T * pInstance )
			{
				return Delegate( pInstance, &method_stub<T, TMethod> );
			}

			bool operator==( const Delegate & i_other )
			{
				return ( i_other.m_pInstance == this->m_pInstance ) && ( i_other.m_pMethod == this->m_pMethod );
			}

			void operator()( Params ... i_Params ) const
			{
				assert( this->m_pMethod );
				( *m_pMethod )( this->m_pInstance, i_Params... );
			}

			void ExecuteIfBound( Params ... i_Params ) const
			{
				if ( m_pInstance )
				{
					assert( m_pMethod );
					if ( m_pMethod == nullptr )
					{
						return;
					}
					( *m_pMethod )( m_pInstance, i_Params ... );
				}
			}

			operator bool() const
			{
				return m_pInstance != nullptr;
			}

			~Delegate()
			{
			}

		private:
			typedef void( *MethodStub )( void * pInstance, Params ... );
			void * m_pInstance;
			MethodStub m_pMethod;

			explicit Delegate( void * i_pInstance, MethodStub i_pMethod ) :
				m_pInstance( i_pInstance ),
				m_pMethod( i_pMethod )
			{
				assert( m_pInstance );
				assert( m_pMethod );
			}

			template<typename T, void( T::*TMethod )( Params... )>
			static void method_stub( void * i_pInstance, Params ... i_Parameters )
			{
				( static_cast<T*>( i_pInstance )->*TMethod )( i_Parameters... );
			}
		};
	}
}