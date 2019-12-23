#include "sChannel.h"
Audio::Channel::sChannel::~sChannel()
{
	const auto result = this->CleanUp();
	if (!result)
	{
		_ASSERT_EXPR( false, L"Destructed the channel failed." );
	}
}