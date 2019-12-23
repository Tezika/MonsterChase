#include <Audio/sChannel.h>
#include <Audio/sContext.h>
#include <Audio/sSoundSource.h>

bool Audio::Channel::sChannel::Initialize( Audio::sContext* i_pContext )
{
	auto result = true;
	static VoiceCallback vcb;
	// Preserve the index 0 as a invalid mark.
	static uint32_t s_channelId = 1;
	ZeroMemory( &m_audioBuffer, sizeof( m_audioBuffer ) );
	m_audioBuffer.pContext = this;
	auto hr = Audio::sContext::g_audioContext.m_pXAudioEngine->CreateSourceVoice( &m_pSourceVoice, &i_pContext->m_audioFormat, 0u, 2.0f, &vcb );
	if (FAILED( hr ))
	{
		_ASSERT_EXPR( false, "Error: creating source voice\n" );
		result = false;
		return result;
	}
	// Assign the channel's ID;
	m_channelId = s_channelId++;
	m_bPaused = false;
	m_audioFormat = i_pContext->m_audioFormat;
	return result;
}

void Audio::Channel::sChannel::PlaySoundBuffer( Audio::Sound::sSoundSource* i_pSound, float i_freqMod, float i_vol, bool i_bLooping )
{
	_ASSERT_EXPR( m_pSourceVoice && !m_pSound, "The channel plays the sound failed." );
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

void Audio::Channel::sChannel::Stop()
{
	_ASSERT_EXPR( m_pSourceVoice && m_pSound, "The channel stops the sound failed." );
	m_pSourceVoice->Stop( 0 );
	m_pSourceVoice->FlushSourceBuffers();
}

void Audio::Channel::sChannel::VoiceCallback::OnBufferEnd( void* i_pBufferContext )
{
	sChannel& channel = *(sChannel*)i_pBufferContext;
	channel.Stop();
	channel.m_pSound->RemoveActiveChannel( &channel );
	channel.m_pSound = nullptr;
	sContext::g_audioContext.DeactivateChannel( &channel );
}

bool Audio::Channel::sChannel::CleanUp()
{
	_ASSERT_EXPR( !m_pSound, "The channel's sound is still available" );
	auto result = true;
	if (m_pSourceVoice)
	{
		m_pSourceVoice->DestroyVoice();
		m_pSourceVoice = nullptr;
	}
	return result;
}

bool Audio::Channel::sChannel::isPlaying()
{
	_ASSERT_EXPR( m_pSourceVoice, "The channel's source voice is inavailable." );
	XAUDIO2_VOICE_STATE state;
	m_pSourceVoice->GetState( &state );
	return state.BuffersQueued > 0 && !m_bPaused;
}

void Audio::Channel::sChannel::Pause()
{
	_ASSERT_EXPR( m_pSound, "The channel has no sound to pause." );
	if (m_bPaused)
	{
		return;
	}
	m_bPaused = true;
	uint32_t opeartionFlag = 0;
	opeartionFlag |= XAUDIO2_PLAY_TAILS;
	m_pSourceVoice->Stop( opeartionFlag );
}

void Audio::Channel::sChannel::Resume()
{
	_ASSERT_EXPR( m_pSound, "The channel has no sound to resume." );
	if (!m_bPaused)
	{
		return;
	}
	m_bPaused = false;
	m_pSourceVoice->Start();
}