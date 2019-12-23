#pragma once
#include <vector>
#include <mutex>
#include "Includes.h"
#include <ReferenceCounting/SmartPtr.h>

#if defined(PLATFORM_WINDOWS)
#include <Audio/Windows/Utilities/WAVFileReader.h>
#endif

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
#if defined(PLATFORM_WINDOWS)
			const wchar_t* m_soundFilePath;
#endif
		};

		struct sSoundSource
		{
		public:
			// Load Interface
			static Engine::SmartPtr<sSoundSource> Create( const std::string& i_path );

			// Populate initialization paratermers1
			static void PopulateSoundInitializationParameters(
				sSoundInitializationParameters& o_soundInitializationParams,
				const wchar_t* i_pSoundFilePath
			);

			void AddChannel( Audio::Channel::sChannel* i_pChannel );
			void RemoveActiveChannel( const Audio::Channel::sChannel* i_pChannel );

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
			~sSoundSource();
		private:
#if defined(PLATFORM_WINDOWS)
			DirectX::WAVData m_wavData;
			std::unique_ptr<BYTE[]> m_pData;
#endif
			std::mutex m_mutex;
			std::vector< Audio::Channel::sChannel*> m_pActiveChannels;

			float m_pitch;
			float m_volume;
			bool m_bLooping;

			sSoundSource() = default;
			// Interfaces
			// Initialization / Clean Up 
			//--------------------------
			bool Initialize( const sSoundInitializationParameters& i_initializationParameters );
			bool CleanUp();
		};
	}
}