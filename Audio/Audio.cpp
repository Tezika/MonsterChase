#include "Audio.h"
#include "sContext.h"
#include <Engine/Asserts/Asserts.h>

eae6320::cResult eae6320::Audio::Initialize( const eae6320::Audio::sAudioInitializationParameters& i_initializationParameters )
{
	auto result = eae6320::Results::Success;
	// Initialize the context
	if (!(result = eae6320::Audio::sContext::g_audioContext.Initialize( i_initializationParameters )))
	{
		EAE6320_ASSERTF( false, "Cannot initialize the audio context" );
		return result;
	}
	return result;
}

eae6320::cResult eae6320::Audio::CleanUp()
{
	auto result = eae6320::Results::Success;
	// Context
	{
		const auto result_context = eae6320::Audio::sContext::g_audioContext.CleanUp();
		if (!result_context)
		{
			result = result_context;
		}
	}
	return result;
}

