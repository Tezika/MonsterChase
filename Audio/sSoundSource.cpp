#include "sSoundSource.h"
#include <algorithm>
#include "sChannel.h"
#include "sContext.h"

namespace Audio
{
	namespace Sound
	{
		Engine::SmartPtr<sSoundSource> sSoundSource::Create( const std::string& i_path )
		{
			Engine::SmartPtr<sSoundSource> ret( nullptr );
			sSoundSource* newSound = nullptr;
			sSoundInitializationParameters initializationParameters;
			// Convert the string path to the wstring
			std::wstring widePath( i_path.begin(), i_path.end() );
			Audio::Sound::sSoundSource::PopulateSoundInitializationParameters( initializationParameters, widePath.c_str() );
			// Allocate a new sound source
			{
				newSound = new (std::nothrow) sSoundSource();
				if (!newSound)
				{
					_ASSERT_EXPR( false, L"Couldn't allocate memory for the sound." );
					return ret;
				}
			}
			// Initialize the platform-specific sound object
			if (!(newSound->Initialize( initializationParameters )))
			{
				_ASSERT_EXPR( false, L"Initialize the new sound failed" );
				return ret;
			}
			newSound->SetLooping( false );
			newSound->SetPitch( 1.0f );
			newSound->SetVolume( 1.0f );
			ret = Engine::SmartPtr<sSoundSource>( newSound );
			return ret;
		}

		void sSoundSource::AddChannel( Audio::Channel::sChannel* i_pChannel )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			m_pActiveChannels.push_back( i_pChannel );
		}

		void sSoundSource::RemoveActiveChannel( const Audio::Channel::sChannel* i_pChannel )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			m_pActiveChannels.erase( std::find(
				m_pActiveChannels.begin(), m_pActiveChannels.end(), i_pChannel ) );
		}

		uint32_t sSoundSource::Play()
		{
			return Audio::sContext::GetInstance().PlaySoundBuffer( this, m_pitch, m_volume, m_bLooping );
		}

		void sSoundSource::Stop( uint32_t i_channelId )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			auto iFoundChannel = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
				[i_channelId]( Audio::Channel::sChannel* pChan ) -> bool
				{
					return i_channelId == pChan->GetChannelId();
				} );
			if (iFoundChannel != m_pActiveChannels.end())
			{
				(*iFoundChannel)->Stop();
			}
		}

		void sSoundSource::Pause( const uint32_t i_channelId )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			_ASSERT_EXPR( i_channelId != 0, L"The channel Id cannot be zero." );
			auto iFoundChannel = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
				[i_channelId]( Audio::Channel::sChannel* pChan ) -> bool
				{
					return i_channelId == pChan->GetChannelId();
				} );
			if (iFoundChannel != m_pActiveChannels.end())
			{
				return (*iFoundChannel)->Pause();
			}
		}

		void sSoundSource::Resume( const uint32_t i_channelId )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			_ASSERT_EXPR( i_channelId != 0, L"The channel Id cannot be zero." );
			auto iFoundChannel = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
				[i_channelId]( Audio::Channel::sChannel* pChan ) -> bool
				{
					return i_channelId == pChan->GetChannelId();
				} );
			if (iFoundChannel != m_pActiveChannels.end())
			{
				return (*iFoundChannel)->Resume();
			}
		}

		bool sSoundSource::isPlaying( const uint32_t i_channelId )
		{
			std::lock_guard<std::mutex> lock( m_mutex );
			if (i_channelId == 0)
			{
				// Find any channel which is playing
				auto iFoundChannel = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
					[]( Audio::Channel::sChannel* pChan ) -> bool
					{
						return pChan->isPlaying();
					} );
				if (iFoundChannel != m_pActiveChannels.end())
				{
					return true;
				}
			}
			else
			{
				// Find the specific channel and check its playing status.
				auto iFoundChannel = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
					[i_channelId]( Audio::Channel::sChannel* pChan ) -> bool
					{
						return i_channelId == pChan->GetChannelId();
					} );
				if (iFoundChannel != m_pActiveChannels.end())
				{
					return (*iFoundChannel)->isPlaying();
				}
			}
			return false;
		}

		sSoundSource::~sSoundSource()
		{
#if defined(PLATFORM_WINDOWS)
			//EAE6320_ASSERT( m_referenceCount == 0 );
			const auto result = CleanUp();
			_ASSERT_EXPR( result, L"Cannot clean up the sound source." );
#endif
		}
	}
}