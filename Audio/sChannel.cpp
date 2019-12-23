#include "sChannel.h"
#include "assert.h"
Audio::Channel::sChannel::~sChannel()
{
	const auto result = this->CleanUp();
	if (!result)
	{
		assert( false, "Destructed the channel failed." );
	}
}