#pragma once
#include <Engine/Results/Results.h>
#include "Includes.h"
#include <mutex>

#if defined(EAE6320_PLATFORM_WINDOWS)
#include <wrl\client.h>
#include <vector>
#endif

#include <memory>

namespace eae6320
{
	namespace Audio
	{
		namespace Sound
		{
			struct sSoundSource;
		}
		namespace Channel
		{
			struct sChannel;
		}
		struct sAudioInitializationParameters;
		struct sContext
		{
		public:
			// Static variable
			static sContext g_audioContext;

			// Initialization / Clean Up
			//--------------------------
			cResult Initialize( const sAudioInitializationParameters& i_initializationParameters );
			cResult CleanUp();
#if defined(EAE6320_PLATFORM_WINDOWS)
			Microsoft::WRL::ComPtr<IXAudio2> m_pXAudioEngine;
			WAVEFORMATEX m_audioFormat;
#endif
			uint32_t PlaySoundBuffer( Audio::Sound::sSoundSource* i_pSound, float i_freqMod, float i_vol, bool i_bLooping );
			void DeactivateChannel( Audio::Channel::sChannel* i_pChannel );
		private:
			sContext() = default;
			~sContext();

#if defined(EAE6320_PLATFORM_WINDOWS)
			void AddNewIdleChannels( const WAVEFORMATEX* i_pWaveFormat );
			IXAudio2MasteringVoice* m_pMasterVoice;
#endif
			std::mutex m_mutex;
			std::vector<std::unique_ptr<Audio::Channel::sChannel>> m_pIdleChannels;
			std::vector<std::unique_ptr<Audio::Channel::sChannel>> m_pActiveChannels;
			size_t m_nMaxiumChannel = 10;
		};
	}
}