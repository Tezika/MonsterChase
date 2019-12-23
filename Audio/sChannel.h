#pragma once
#include "Includes.h"
#include "sSoundSource.h"
namespace Audio
{
	struct sContext;
	namespace Sound
	{
		struct sSoundSource;
	}
	namespace Channel
	{
		struct sChannel
		{
		public:
			bool Initialize( sContext* i_pContext );
			bool CleanUp();
			void PlaySoundBuffer( Audio::Sound::sSoundSource* i_pSound, float i_freqMod, float i_vol, bool looping );
			void Stop();
			void Pause();
			void Resume();
			bool isPlaying();
			// Make it public because the other class would reference it.
			sChannel() = default;
			~sChannel();
			inline void SetVolume( float i_volume ) { m_pSourceVoice->SetVolume( i_volume ); };
			inline void SetPitch( float i_pitch ) { m_pSourceVoice->SetFrequencyRatio( i_pitch ); };

			inline uint32_t GetChannelId() { return m_channelId; }
#if defined(PLATFORM_WINDOWS)
			inline const WAVEFORMATEX& GetWaveFormat() { return m_audioFormat; };
#endif

		private:
#if defined(PLATFORM_WINDOWS)
			XAUDIO2_BUFFER m_audioBuffer;
			IXAudio2SourceVoice* m_pSourceVoice;
			// does this need to be synchronized?
			// (no--no overlap of callback thread and main thread here)
			Audio::Sound::sSoundSource* m_pSound;
			WAVEFORMATEX m_audioFormat;
#endif
			uint32_t m_channelId;
			bool m_bPaused;
			class VoiceCallback : public IXAudio2VoiceCallback
			{
			public:
				void STDMETHODCALLTYPE OnStreamEnd() override
				{}
				void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override
				{}
				void STDMETHODCALLTYPE OnVoiceProcessingPassStart( UINT32 SamplesRequired ) override
				{}
				void STDMETHODCALLTYPE OnBufferEnd( void* pBufferContext ) override;
				void STDMETHODCALLTYPE OnBufferStart( void* pBufferContext ) override
				{}
				void STDMETHODCALLTYPE OnLoopEnd( void* pBufferContext ) override
				{}
				void STDMETHODCALLTYPE OnVoiceError( void* pBufferContext, HRESULT Error ) override
				{}
			};
		};
	}
}