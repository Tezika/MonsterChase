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
#include "Windows.h"

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
		Game( Game const & );
		void operator=( Game const & );

	public:
		bool Initialize( HINSTANCE i_hInstance, int i_nCmdShow );
		void Run();
		void Destroy();

		bool ShouldEnd() { return m_bEnd; }
		void TriggerEnd() { m_bEnd = true; }
		int ClampForMap( int val, int maxiumVal );
		Player * GetCurPlayer() { return m_pPlayer; }
		inline const int GetGridWidth() { return m_grid_Width; }
		inline const int GetGridHeight() { return m_grid_Height; }

	private:
		Player * m_pPlayer;
		EnemyManager * m_pEnemyManager;
		int m_grid_Width;
		int m_grid_Height;
		bool m_bEnd;
		int  m_roundTimer_newEnemy;
	};
}

#endif /* game_h */
