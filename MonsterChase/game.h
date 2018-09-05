//
//  game.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef game_h
#define game_h

#include <iostream>
#include "enemymanager.h"
#include "player.h"

namespace MonsterChase
{
	//This is a Singleton.
	class Game
	{
	public:
		static Game& GetInstance()
		{
			static Game game;
			return game;
		}

	private:
		Game();
		Game(Game const&);
		void operator=(Game const&);

	public:
		void Initialize();
		void Run();
		void Stop();
		int GetGridWidth() { return grid_width_; }
		int GetGridHeight() { return grid_height_; }
		bool ShouldEnd() { return end_; }
		void TriggerEnd() { end_ = true; }
		int ClampForMap(int val, int maxiumVal);
		Player* GetCurPlayer() { return player_; }

	private:
		Player * player_;
		EnemyManager* enemyManager_;
		int grid_width_;
		int grid_height_;
		bool end_;
		int  roundTimer_newEnemy_;
	};
}

#endif /* game_h */
