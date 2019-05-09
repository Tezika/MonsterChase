//
//  game.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//
#pragma once
#include <iostream>
#include "player.h"
#include "ball.h"
#include "wall.h"
#include "SmartPtr.h"

namespace FinalProject
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

		Game( Game const & ) = delete;
		Game & operator=( Game const & ) = delete;

	private:
		Game();

	public:
		bool Initialize();
		void Run();
		void Reset();
		void Destroy();

		bool ShouldEnd() { return m_bEnd; }
		void TriggerEnd() { m_bEnd = true; }
		Engine::SmartPtr<Player> GetPlayer1(){ return m_player_1; };
		Engine::SmartPtr<Player> GetPlayer2(){ return m_player_2; };

	private:
		Engine::SmartPtr<Player> m_player_1;
		Engine::SmartPtr<Player> m_player_2;

		Engine::SmartPtr<Ball> m_ball;

		Engine::SmartPtr<Wall> m_wall_bottom;
		Engine::SmartPtr<Wall> m_wall_up;
		Engine::SmartPtr<Wall> m_wall_left;
		Engine::SmartPtr<Wall> m_wall_right;

		void InitializePlayer( const Engine::SmartPtr<Player> & i_player );
		void SetupWalls();
		bool m_bEnd;
	};
}
