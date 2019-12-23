#include "Audio.h"
#include "sContext.h"
#include "assert.h"

bool Audio::Initialize( const Audio::sAudioInitializationParameters& i_initializationParameters )
{
	auto result = true;
	// Initialize the context
	if (!(result = Audio::sContext::g_audioContext.Initialize( i_initializationParameters )))
	{
		assert( false, "Cannot initialize the audio context" );
		return result;
	}
	return result;
}

bool Audio::CleanUp()
{
	auto result = true;
	// Context
	{
		const auto result_context = Audio::sContext::g_audioContext.CleanUp();
		if (!result_context)
		{
			result = result_context;
		}
	}
	return result;
}