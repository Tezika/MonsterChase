#include <Engine/Audio/sChannel.h>
#include <Engine/Audio/sContext.h>
#include <Engine/Audio/sSoundSource.h>
#include <Engine/Results/cResult.h>
#include <Engine/Asserts/Asserts.h>

eae6320::cResult eae6320::Audio::Channel::sChannel::Initialize( eae6320::Audio::sContext* i_pContext )
{
	auto result = eae6320::Results::Success;
	static VoiceCallback vcb;
	// Preserve the index 0 as a invalid mark.
	static uint32_t s_channelId = 1;
	ZeroMemory( &m_audioBuffer, sizeof( m_audioBuffer ) );
	m_audioBuffer.pContext = this;
	auto hr = eae6320::Audio::sContext::g_audioContext.m_pXAudioEngine->CreateSourceVoice( &m_pSourceVoice, &i_pContext->m_audioFormat, 0u, 2.0f, &vcb );
	if (FAILED( hr ))
	{
		EAE6320_ASSERTF( false, "Error %#X creating source voice\n", hr );
		result = Results::Failure;
		return result;
	}
	// Assign the channel's ID;
	m_channelId = s_channelId++;
	m_bPaused = false;
	m_audioFormat = i_pContext->m_audioFormat;
	return result;
}

void eae6320::Audio::Channel::sChannel::PlaySoundBuffer( Audio::Sound::sSoundSource* i_pSound, float i_freqMod, float i_vol, bool i_bLooping )
{
	EAE6320_ASSERTF( m_pSourceVoice && !m_pSound, "The channel plays the sound failed." );
	i_pSound->AddChannel( this );
	// Callback thread not running yet, so no sync necessary for pSound
	m_pSound = i_pSound;
	// Set the audio buffer information
	m_audioBuffer.pAudioData = i_pSound->GetAudioData().get();
	m_audioBuffer.AudioBytes = i_pSound->GetWavData().audioBytes;
	m_audioBuffer.LoopCount = i_bLooping ? XAUDIO2_LOOP_INFINITE : 0;
	m_pSourceVoice->SubmitSourceBuffer( &m_audioBuffer, nullptr );
	m_pSourceVoice->SetFrequencyRatio( i_freqMod );
	m_pSourceVoice->SetVolume( i_vol );
	m_pSourceVoice->Start();
}

void eae6320::Audio::Channel::sChannel::Stop()
{
	EAE6320_ASSERTF( m_pSourceVoice && m_pSound, "The channel stops the sound failed." );
	m_pSourceVoice->Stop( 0 );
	m_pSourceVoice->FlushSourceBuffers();
}

void eae6320::Audio::Channel::sChannel::VoiceCallback::OnBufferEnd( void* i_pBufferContext )
{
	sChannel& channel = *(sChannel*)i_pBufferContext;
	channel.Stop();
	channel.m_pSound->RemoveActiveChannel( &channel );
	channel.m_pSound = nullptr;
	sContext::g_audioContext.DeactivateChannel( &channel );
}

eae6320::cResult eae6320::Audio::Channel::sChannel::CleanUp()
{
	EAE6320_ASSERTF( !m_pSound, "The channel's sound is still available" );
	auto result = eae6320::Results::Success;
	if (m_pSourceVoice)
	{
		m_pSourceVoice->DestroyVoice();
		m_pSourceVoice = nullptr;
	}
	return result;
}

bool eae6320::Audio::Channel::sChannel::isPlaying()
{
	EAE6320_ASSERTF( m_pSourceVoice, "The channel's source voice is inavailable." );
	XAUDIO2_VOICE_STATE state;
	m_pSourceVoice->GetState( &state );
	return state.BuffersQueued > 0 && !m_bPaused;
}

void eae6320::Audio::Channel::sChannel::Pause()
{
	EAE6320_ASSERTF( m_pSound, "The channel has no sound to pause." );
	if (m_bPaused)
	{
		return;
	}
	m_bPaused = true;
	uint32_t opeartionFlag = 0;
	opeartionFlag |= XAUDIO2_PLAY_TAILS;
	m_pSourceVoice->Stop( opeartionFlag );
}

void eae6320::Audio::Channel::sChannel::Resume()
{
	EAE6320_ASSERTF( m_pSound, "The channel has no sound to resume." );
	if (!m_bPaused)
	{
		return;
	}
	m_bPaused = false;
	m_pSourceVoice->Start();
}