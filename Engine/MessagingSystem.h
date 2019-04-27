#pragma once

namespace Engine
{
	// Use the TString class as a temporary solution. It'll change into the HashedString soon.
	class TString;
	namespace MessagingSystem
	{
		typedef void( *MessageHandler_t )( const TString & i_Message );

		void RegisterMessageHandler( const TString & i_Message, MessageHandler_t i_pHandler );
	}
}