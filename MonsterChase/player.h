//
//  player.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef player_h
#define player_h
#include "entity.h"

namespace MonsterChase
{
	class Player : public Entity
	{
	public:
		Player();
		Player(const Engine::TString & name, const Engine::Point2D<float> & i_position, int health);
		~Player();
		void PrintOutInfo() override;

	private:

	};
}

#endif /* player_h */
