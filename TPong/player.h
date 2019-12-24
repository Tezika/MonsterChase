#pragma once
#include "entity.h"
namespace TPong
{
	class Player :public Entity
	{
	public:
		Player() = default;
		Player( const Player& ) = delete;
		Player& operator=( const Player& ) = delete;
		virtual ~Player();
	};
}
