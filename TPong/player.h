#pragma once

namespace TPong
{
	class Player
	{
	public:
		Player();
		Player( const Engine::HashedString& i_name, const Engine::Vector3SSE& i_position );
		virtual ~Player();
	};
}
