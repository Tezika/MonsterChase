#include "stdafx.h"
#include "MessagingSystem.h"
#include "TString.h"
#include "MultiCastDelegate.h"

namespace Engine
{
	namespace Messaging
	{
		void MessageSystem::RegisterMessageHandler( const TString & i_Message, Delegate<> & i_Delegate )
		{
			std::unordered_map<char*, MultiCastDelegate<>>::iterator itr;
			itr = m_Message2Delegates.find( i_Message.c_str() );
			if ( itr == m_Message2Delegates.end() )
			{
				MultiCastDelegate<> newMultiCastDelegate;
				newMultiCastDelegate.AddDelegate( i_Delegate );
				m_Message2Delegates.insert( std::make_pair( i_Message.c_str(), newMultiCastDelegate ) );
			}
			else
			{
				itr->second.AddDelegate( i_Delegate );
			}
		}

		void MessageSystem::DeregisterMessageHandler( const TString & i_Message, Delegate<> & i_Delegate )
		{
			std::unordered_map<char*, MultiCastDelegate<>>::iterator itr;
			itr = m_Message2Delegates.find( i_Message.c_str() );
			if ( itr == m_Message2Delegates.end() )
			{
				return;
			}
			else
			{
				itr->second.RemoveDelegate( i_Delegate );
			}
		}

		void MessageSystem::SendMessage( const TString & i_Message )
		{
			if ( m_Message2Delegates.find( i_Message.c_str() ) != m_Message2Delegates.end() )
			{
				m_Message2Delegates[i_Message.c_str()].ExecuteIfBound();
			}
		}
	}
}