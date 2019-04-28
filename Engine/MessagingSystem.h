#pragma once
#include <unordered_map>
#include "MultiCastDelegate.h"
namespace Engine
{
	class TString;
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

			void RegisterMessageDelegate( const char *  i_Message, Delegate<> & i_Delegate );
			void DeregisterMessageDelegate( const char * i_Message, Delegate<> & i_Delegate );
			void SendMessageW( const char * i_Message );

		private:
			std::unordered_map<const char*, MultiCastDelegate<>> m_Message2Delegates;
			MessageSystem(){};
		};
	}
}
