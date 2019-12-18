#pragma once
#if defined( EAE6320_PLATFORM_WINDOWS )
#include <Engine/Windows/Includes.h>
#endif

#include <Engine/Results/Results.h>

namespace eae6320
{
	namespace Audio
	{
		struct sAudioInitializationParameters
		{

		};
		cResult Initialize( const sAudioInitializationParameters& i_initializationParameters );
		cResult CleanUp();
	}
}