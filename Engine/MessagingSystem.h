#pragma once
#include <unordered_map>
namespace Engine
{
	class TString;
	// Use the TString class as a temporary solution. It'll change into the HashedString soon.
	namespace Messaging
	{
		template<class...Params>
		class Delegate;

		template<class...Params>
		class MultiCastDelegate;

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

			void RegisterMessageHandler( const TString & i_Message, Delegate<> & i_Delegate );
			void DeregisterMessageHandler( const TString & i_Message, Delegate<> & i_Delegate );
			void SendMessage( const TString & i_Message );

		private:
			std::unordered_map<char*, MultiCastDelegate<>> m_Message2Delegates;
			MessageSystem(){};
		};
	}
}
