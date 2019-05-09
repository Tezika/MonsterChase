//
//  player.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#pragma once
#include "entity.h"

namespace FinalProject
{
	class Player : public Entity
	{
	public:
		Player();
		Player( const Engine::TString & name, const Engine::Vector3SSE & i_position );
		~Player();
	};
}
