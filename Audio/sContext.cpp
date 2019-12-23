#include "sContext.h"
#include <algorithm>
#include "sChannel.h"

Audio::sContext Audio::sContext::g_audioContext;
Audio::sContext::~sContext()
{
	const auto result = this->CleanUp();
	_ASSERT_EXPR( result, "Cannot clean up the audio context." );
}

void Audio::sContext::DeactivateChannel( Audio::Channel::sChannel* i_pChannel )
{
	std::lock_guard<std::mutex> lock( m_mutex );
	auto i = std::find_if( m_pActiveChannels.begin(), m_pActiveChannels.end(),
		[i_pChannel]( const std::unique_ptr<Audio::Channel::sChannel>& pChan ) -> bool
		{
			return i_pChannel == pChan.get();
		} );
	m_pIdleChannels.push_back( std::move( *i ) );
	m_pActiveChannels.erase( i );
}