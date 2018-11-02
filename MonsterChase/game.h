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

		bool ShouldEnd() { return m_bBool_; }
		void TriggerEnd() { m_bBool_ = true; }
		int ClampForMap(int val, int maxiumVal);
		Player* GetCurPlayer() { return m_pPlayer_; }
		inline const int GetGridWidth() { return m_Grid_Width_; }
		inline const int GetGridHeight() { return m_Grid_Height_; }

	private:
		Player * m_pPlayer_;
		EnemyManager * m_pEnemyManager_;
		int m_Grid_Width_;
		int m_Grid_Height_;
		bool m_bBool_;
		int  m_roundTimer_newEnemy_;
	};
}

#endif /* game_h */
