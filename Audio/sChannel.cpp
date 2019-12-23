#include "sChannel.h"
Audio::Channel::sChannel::~sChannel()
{
	const auto result = this->CleanUp();
	if (!result)
	{
		_ASSERT_EXPR( false, "Destructed the channel failed." );
	}
}