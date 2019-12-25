#include "Audio.h"
#include "sContext.h"

bool Audio::Initialize( const Audio::sAudioInitializationParameters& i_initializationParameters )
{
	auto result = true;
	// Initialize the context
	if (!(result = Audio::sContext::GetInstance().Initialize( i_initializationParameters )))
	{
		_ASSERT_EXPR( false, L"Cannot initialize the audio context" );
		return result;
	}
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
	return result;
}