//
//  player.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef player_h
#define player_h

#include "object.h"

namespace MonsterChase
{
	class Player : public Object
	{
	public:
		Player();
		Player(char* name, int moveSpeed, int health);
		~Player();
		void Move() override;
		void PrintOutInfo() override;

	private:

	};
}

#endif /* player_h */
