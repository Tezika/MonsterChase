#include "stdafx.h"
#include "MessageSystem.h"
#include "TString.h"
#include "MultiCastDelegate.h"


namespace Engine
{
	namespace Messaging
	{
		void MessageSystem::RegisterMessageDelegate( const HashedString & i_Message, Delegate<void *> & i_Delegate )
		{
			std::map<HashedString, MultiCastDelegate<void *>>::iterator itr;
			itr = m_pMessage2Delegates->find( i_Message );
			if ( itr == m_pMessage2Delegates->end() )
			{
				MultiCastDelegate<void *> newMultiCastDelegate;
				newMultiCastDelegate.AddDelegate( i_Delegate );
				m_pMessage2Delegates->insert( std::make_pair( i_Message, newMultiCastDelegate ) );
			}
			else
			{
				itr->second.AddDelegate( i_Delegate );
			}
		}

		void MessageSystem::DeregisterMessageDelegate( const HashedString & i_Message, Delegate<void *> & i_Delegate )
		{
			std::map<HashedString, MultiCastDelegate<void *>>::iterator itr;
			itr = m_pMessage2Delegates->find( i_Message );
			if ( itr == m_pMessage2Delegates->end() )
			{
				return;
			}
			else
			{
				itr->second.RemoveDelegate( i_Delegate );
			}
		}

		void MessageSystem::SendMessageW( const HashedString & i_Message, void * i_pInfo )
		{
			std::map<HashedString, MultiCastDelegate<void *>>::iterator itr;
			itr = m_pMessage2Delegates->find( i_Message );
			if ( itr != m_pMessage2Delegates->end() )
			{
				itr->second.ExecuteIfBound( i_pInfo );
			}
		}

		bool MessageSystem::Initialize()
		{
			m_pMessage2Delegates = new std::map<HashedString, MultiCastDelegate<void *>>();
			assert( m_pMessage2Delegates != nullptr );
			return true;
		}

		bool MessageSystem::Destroy()
		{
			m_pMessage2Delegates->clear();
			delete m_pMessage2Delegates;
			m_pMessage2Delegates = nullptr;
			return true;
		}
	}
}