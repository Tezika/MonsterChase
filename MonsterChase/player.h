//
//  player.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#pragma once
#include "entity.h"

namespace TPong
{
	class Player : public Entity
	{
	public:
		Player();
		Player( const Engine::HashedString & name, const Engine::Vector3SSE & i_position );
		void Initialize();
		void Destroy();
		~Player();
	};
}
