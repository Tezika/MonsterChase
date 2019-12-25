#include "Audio.h"
#include "sContext.h"
#include <Engine/ConsolePrint.h>

bool Audio::Initialize( const Audio::sAudioInitializationParameters& i_initializationParameters )
{
	auto result = true;
	// Initialize the context
	if (!(result = Audio::sContext::GetInstance().Initialize( i_initializationParameters )))
	{
		_ASSERT_EXPR( false, L"Cannot initialize the audio context" );
		return result;
	}
	DEBUG_PRINT_ENGINE( "The audio system initialized successfully." );
	return result;
}

bool Audio::CleanUp()
{
	auto result = true;
	// Context
	{
		const auto result_context = Audio::sContext::GetInstance().CleanUp();
		if (!result_context)
		{
			result = result_context;
		}
	}
	DEBUG_PRINT_ENGINE( "The audio system shutdown successfully." );
	return result;
}