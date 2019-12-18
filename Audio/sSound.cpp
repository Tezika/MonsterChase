#include "sSound.h"
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Asserts/Asserts.h>
#include <algorithm>
#include "sChannel.h"
#include "sContext.h"

eae6320::Assets::cManager<eae6320::Audio::Sound::sSoundSource> eae6320::Audio::Sound::sSoundSource::s_manager;

namespace eae6320
{
	namespace Audio
	{
		namespace Sound
		{
			eae6320::cResult sSoundSource::Load( const std::string& i_path, sSoundSource*& o_pSound )
			{
				auto result = Results::Success;
				sSoundSource* newSound = nullptr;
				cScopeGuard scopeGuard( [&o_pSound, &result, &newSound]
					{
						if (result)
						{
							EAE6320_ASSERT( newSound != nullptr );
							o_pSound = newSound;
						}
						else
						{
							if (newSound)
							{
								newSound->DecrementReferenceCount();
								newSound = nullptr;
							}
							o_pSound = nullptr;
						}
					} );
				sSoundInitializationParameters initializationParameters;
				// Convert the string path to the wstring.
				std::wstring widePath( i_path.begin(), i_path.end() );
				Audio::Sound::sSoundSource::PopulateSoundInitializationParameters( initializationParameters, widePath.c_str() );
				// Allocate a new effect
				{
					newSound = new (std::nothrow) sSoundSource();
					if (!newSound)
					{
						result = Results::OutOfMemory;
						EAE6320_ASSERTF( false, "Couldn't allocate memory for the sound." );
						Logging::OutputError( "Failed to allocate memory for the sound." );
						return result;
					}
				}
				// Initialize the platform-specific sound object
				if (!(result = newSound->Initialize( initializationParameters )))
				{
					EAE6320_ASSERTF( false, "Initialize the new sound failed" );
					return result;
				}
				newSound->SetLooping( false );
				newSound->SetPitch( 1.0f );
				newSound->SetVolume( 1.0f );
				return result;
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
				return Audio::sContext::g_audioContext.PlaySoundBuffer( this, m_pitch, m_volume, m_bLooping );
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

			sSoundSource::~sSoundSource()
			{
#if defined(EAE6320_PLATFORM_WINDOWS)
				EAE6320_ASSERT( m_referenceCount == 0 );
				const auto result = CleanUp();
				EAE6320_ASSERT( result );
#endif
			}
		}
	}
}