#pragma once
#include <Engine/Assets/ReferenceCountedAssets.h>
#include <Engine/Assets/cHandle.h>
#include <Engine/Assets/cManager.h>
#include <mutex>
#include "Includes.h"

#if defined(EAE6320_PLATFORM_WINDOWS)
#include <Engine/Audio/Windows/Utilities/WAVFileReader.h>
#endif

namespace eae6320
{
	namespace Audio
	{
		namespace Channel
		{
			struct sChannel;
		}
		namespace Sound
		{
			struct sSoundInitializationParameters
			{
				sSoundInitializationParameters() = default;
#if defined(EAE6320_PLATFORM_WINDOWS)
				const wchar_t* m_soundFilePath;
#endif
			};

			struct sSoundSource
			{
			public:
				// Assets
				using Handle = Assets::cHandle<sSoundSource>;
				static Assets::cManager<sSoundSource> s_manager;

				// Load Interface
				static cResult Load( const std::string& i_path, sSoundSource*& o_pSound );

				// Populate initialization paratermers
				static void PopulateSoundInitializationParameters(
					sSoundInitializationParameters& o_soundInitializationParams,
					const wchar_t* i_pSoundFilePath
				);

				void AddChannel( Audio::Channel::sChannel* i_pChannel );
				void RemoveActiveChannel( const Audio::Channel::sChannel* i_pChannel );

#if defined(EAE6320_PLATFORM_WINDOWS)
				EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS();
				EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS( sSoundSource );
#endif
				// =========
				// Interfaces
				// =========
				uint32_t Play();
				void Stop( uint32_t i_channelId );

				void Pause( const uint32_t i_channelId );
				void Resume( const uint32_t i_channelId );

				inline float GetPitch() { return m_pitch; };
				// "Pitch" is the quality that makes it possible to judge sounds as "higher" and "lower" in the sense associated with musical melodies.
				//  The value is lower than 1.0 would be much more lower, otherwise be much more higher.
				void SetPitch( float i_pitch ) { m_pitch = i_pitch; };

				inline float GetVolume() { return m_volume; };
				// "Volume" should be 0.0 ~ 1.0
				inline void SetVolume( float i_volume ) { m_volume = i_volume; };

				inline bool isLooping() { return m_bLooping; };
				inline void SetLooping( bool i_bLooping ) { m_bLooping = i_bLooping; };

				bool isPlaying( const uint32_t i_channelId = 0 );

				inline DirectX::WAVData& GetWavData() { return m_wavData; };
				inline std::unique_ptr<BYTE[]>& GetAudioData() { return m_pData; };
			private:
#if defined(EAE6320_PLATFORM_WINDOWS)
				EAE6320_ASSETS_DECLAREREFERENCECOUNT();
				DirectX::WAVData m_wavData;
				std::unique_ptr<BYTE[]> m_pData;
#endif
				std::mutex m_mutex;
				std::vector< Audio::Channel::sChannel*> m_pActiveChannels;

				float m_pitch;
				float m_volume;
				bool m_bLooping;

				sSoundSource() = default;
				~sSoundSource();

				// Interfaces
				// Initialization / Clean Up 
				//--------------------------
				cResult Initialize( const sSoundInitializationParameters& i_initializationParameters );
				cResult CleanUp();
			};
		}
	}
}