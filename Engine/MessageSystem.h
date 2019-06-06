#pragma once
#include <map>
#include "MultiCastDelegate.h"
#include "HashedString.h"

namespace Engine
{
	class HashedString;

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

			void RegisterMessageDelegate( const HashedString & i_Message, Delegate<void *> & i_Delegate );
			void DeregisterMessageDelegate( const HashedString & i_Message, Delegate< void *> & i_Delegate );
			void SendMessageW( const HashedString & i_Message, void * info );

			bool Initialize();
			bool Destroy();

		private:
			std::map<HashedString, MultiCastDelegate<void *>> * m_pMessage2Delegates;
			MessageSystem() {};
		};
	}
}