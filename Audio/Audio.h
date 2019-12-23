#pragma once
namespace Audio
{
	struct sAudioInitializationParameters
	{

	};
	bool Initialize( const sAudioInitializationParameters& i_initializationParameters );
	bool CleanUp();
}