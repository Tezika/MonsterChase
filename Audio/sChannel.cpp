#include "sChannel.h"
#include <Engine/Asserts/Asserts.h>

eae6320::Audio::Channel::sChannel::~sChannel()
{
	const auto result = this->CleanUp();
	if (!result)
	{
		EAE6320_ASSERTF( false, "Destruct the channel failed." );
	}
}