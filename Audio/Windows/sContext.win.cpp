// Use the preprocessor to guard that this cpp file is only compiled in Windows platform.
#if defined(PLATFORM_WINDOWS)
#include <Audio/sChannel.h>
#include <Audio/Audio.h>
#include <Audio/sContext.h>
#include <Audio/sSoundSource.h>
#include <Audio/sChannel.h>
#include <algorithm>

namespace
{
	bool CheckForTwoWaveFormats( const WAVEFORMATEX& i_pFormat_1, const WAVEFORMATEX& i_pFormat_2 )
	{
		return
			(i_pFormat_1.wFormatTag == i_pFormat_2.wFormatTag) &&
			(i_pFormat_1.nChannels == i_pFormat_2.nChannels) &&
			(i_pFormat_1.nSamplesPerSec == i_pFormat_2.nSamplesPerSec) &&
			(i_pFormat_1.nAvgBytesPerSec == i_pFormat_2.nAvgBytesPerSec) &&
			(i_pFormat_1.wBitsPerSample == i_pFormat_2.wBitsPerSample) &&
			(i_pFormat_1.nBlockAlign == i_pFormat_2.nBlockAlign) &&
			(i_pFormat_1.cbSize == i_pFormat_2.cbSize);
	}
}

bool Audio::sContext::Initialize( const Audio::sAudioInitializationParameters& i_initializationParamters )
{
	auto result = true;
	//
	// Initialize XAudio2
	//
	auto hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
	if (FAILED( hr ))
	{
		_ASSERT_EXPR( false, L"Failed to init COM." );
		result = false;
		return result;
	}

	UINT32 flags = 0;
#if (_WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif
	hr = XAudio2Create( m_pXAudioEngine.GetAddressOf(), flags );
	if (FAILED( hr ))
	{
		_ASSERT_EXPR( false, L"Failed to init XAudio2 engine" );
		result = false;
		CoUninitialize();
		return result;
	}
	//
	// Setup the debugging options
	//
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
	// To see the trace output, you need to view ETW logs for this application:
	//    Go to Control Panel, Administrative Tools, Event Viewer.
	//    View->Show Analytic and Debug Logs.
	//    Applications and Services Logs / Microsoft / Windows / XAudio2. 
	//    Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK 
	XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS | XAUDIO2_LOG_INFO | XAUDIO2_LOG_DETAIL | XAUDIO2_LOG_FUNC_CALLS;
	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	m_pXAudioEngine->SetDebugConfiguration( &debug, 0 );
#endif

	//
	// Create the master voice
	//
	m_pMasterVoice = nullptr;
	if (FAILED( hr = m_pXAudioEngine->CreateMasteringVoice( &m_pMasterVoice ) ))
	{
		_ASSERT_EXPR( false, L"Failed creating mastering voice" );
		m_pXAudioEngine.Reset();
		CoUninitialize();
		result = false;
		return result;
	}
	return result;
}

bool Audio::sContext::CleanUp()
{
	auto result = true;
	for (size_t i = 0; i < m_pIdleChannels.size(); i++)
	{
		m_pIdleChannels[i].reset();
	}
	m_pIdleChannels.clear();
	for (size_t i = 0; i < m_pActiveChannels.size(); i++)
	{
		m_pActiveChannels[i].reset();
	}
	m_pActiveChannels.clear();
	m_pMasterVoice = nullptr;
	CoUninitialize();
	return result;
}

uint32_t Audio::sContext::PlaySoundBuffer( Audio::Sound::sSoundSource* i_pSound, float i_freqMod, float i_vol, bool i_bLooping )
{
	std::lock_guard<std::mutex> lock( m_mutex );
	const auto pWaveData = i_pSound->GetWavData();
	// IF there is any channel's here
	if (m_pIdleChannels.size() > 0)
	{
		const auto* pWaveFormat = i_pSound->GetWavData().wfx;
		size_t idx_channel = -1;
		for (size_t i = 0; i < m_pIdleChannels.size(); i++)
		{
			if (CheckForTwoWaveFormats( *pWaveFormat, m_pIdleChannels[i]->GetWaveFormat() ))
			{
				idx_channel = i;
				break;
			}
		}
		if (idx_channel != -1)
		{
			m_pActiveChannels.push_back( std::move( m_pIdleChannels[idx_channel] ) );
			m_pIdleChannels.erase( std::find( m_pIdleChannels.begin(), m_pIdleChannels.end(), m_pIdleChannels[idx_channel] ) );
			m_pActiveChannels.back()->PlaySoundBuffer( i_pSound, i_freqMod, i_vol, i_bLooping );
			return m_pActiveChannels.back().get()->GetChannelId();
		}
	}
	// Add the certain format's channel
	this->AddNewIdleChannels( i_pSound->GetWavData().wfx );
	m_pActiveChannels.push_back( std::move( m_pIdleChannels.back() ) );
	m_pIdleChannels.pop_back();
	m_pActiveChannels.back()->PlaySoundBuffer( i_pSound, i_freqMod, i_vol, i_bLooping );
	return m_pActiveChannels.back().get()->GetChannelId();
}

void Audio::sContext::AddNewIdleChannels( const WAVEFORMATEX* i_pFormat )
{
	// Updated the audio formats
	m_audioFormat.wFormatTag = i_pFormat->wFormatTag;
	m_audioFormat.nChannels = i_pFormat->nChannels;
	m_audioFormat.nSamplesPerSec = i_pFormat->nSamplesPerSec;
	m_audioFormat.nAvgBytesPerSec = i_pFormat->nAvgBytesPerSec;
	m_audioFormat.nBlockAlign = i_pFormat->nBlockAlign;
	m_audioFormat.wBitsPerSample = i_pFormat->wBitsPerSample;
	m_audioFormat.cbSize = i_pFormat->cbSize;

	for (uint8_t i = 0; i < m_nMaxiumChannel; i++)
	{
		m_pIdleChannels.push_back( std::make_unique<Audio::Channel::sChannel>() );
		m_pIdleChannels.back().get()->Initialize( this );
	}
}
#endif