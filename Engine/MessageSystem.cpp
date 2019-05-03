#include "stdafx.h"
#include "MessageSystem.h"
#include "TString.h"
#include "MultiCastDelegate.h"


namespace Engine
{
	namespace Messaging
	{
		void MessageSystem::RegisterMessageDelegate( const HashedString & i_Message, Delegate<> & i_Delegate )
		{
			std::map<HashedString, MultiCastDelegate<>>::iterator itr;
			itr = m_Message2Delegates.find( i_Message );
			if ( itr == m_Message2Delegates.end() )
			{
				MultiCastDelegate<> newMultiCastDelegate;
				newMultiCastDelegate.AddDelegate( i_Delegate );
				m_Message2Delegates.insert( std::make_pair( i_Message, newMultiCastDelegate ) );
			}
			else
			{
				itr->second.AddDelegate( i_Delegate );
			}
		}

		void MessageSystem::DeregisterMessageDelegate( const HashedString & i_Message, Delegate<> & i_Delegate )
		{
			std::map<HashedString, MultiCastDelegate<>>::iterator itr;
			itr = m_Message2Delegates.find( i_Message );
			if ( itr == m_Message2Delegates.end() )
			{
				return;
			}
			else
			{
				itr->second.RemoveDelegate( i_Delegate );
			}
		}

		void MessageSystem::SendMessageW( const HashedString & i_Message )
		{
			if ( m_Message2Delegates.find( i_Message ) != m_Message2Delegates.end() )
			{
				m_Message2Delegates[i_Message].ExecuteIfBound();
			}
		}

		bool MessageSystem::Destroy()
		{
			return true;
		}
	}
}