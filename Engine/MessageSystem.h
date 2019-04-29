#pragma once
#include <map>
#include "MultiCastDelegate.h"
#include "HashString.h"

namespace Engine
{
	class TString;
	class HashedString;
	// Use the TString class as a temporary solution. It'll change into the HashedString soon.
	// It only supports the method with 0 augment right now.
	namespace Messaging
	{
		class MessageSystem
		{
		public:
			static MessageSystem& GetInstance()
			{
				static MessageSystem instance;
				return instance;

			}
			MessageSystem( MessageSystem const& ) = delete;
			void operator=( MessageSystem const& ) = delete;

			void RegisterMessageDelegate( const HashedString & i_Message, Delegate<> & i_Delegate );
			void DeregisterMessageDelegate( const HashedString & i_Message, Delegate<> & i_Delegate );
			void SendMessageW( const HashedString & i_Message );

		private:
			std::map<HashedString, MultiCastDelegate<>> m_Message2Delegates;
			MessageSystem(){};
		};
	}
}
