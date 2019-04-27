#pragma once

namespace Engine
{
	class TString;
	namespace MessagingSystem
	{
		typedef void( *MessageHandler_t )( const TString & i_str );

	}
}