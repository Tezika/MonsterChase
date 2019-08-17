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
#include "Delegate.h"
#include "Vector3SSE.h"

namespace FinalProject
{
	using SPP = Engine::SmartPtr<Player>;
	using SPB = Engine::SmartPtr<Ball>;
	using SPW = Engine::SmartPtr<Wall>;
	using SPG = Engine::SmartPtr<Engine::GameObject>;
	using VEC3SEE = Engine::Vector3SSE;
	using HSS = Engine::HashedString;
	using DEL = Engine::Messaging::Delegate<void*>;

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
		void Restart();
		void Destroy();

		inline bool ShouldEnd() { return m_bEnd; };
		inline void TriggerEnd() { m_bEnd = true; };
		inline bool InPaused() { return m_bPause; };
		inline void TooglePause() { m_bPause = !m_bPause; };
		SPP & GetPlayer1() { return m_player_1; };
		SPP & GetPlayer2() { return m_player_2; };

	private:
		// Players
		SPP m_player_1;
		SPP m_player_2;

		// Ball
		SPB m_ball;

		// Walls
		SPW m_wall_bottom;
		SPW m_wall_up;
		SPW m_wall_left;
		SPW m_wall_right;

		// Delegates
		DEL m_dBallCollideDeadWall;

		// Cached Position
		VEC3SEE m_cachedStartPosition_player1;
		VEC3SEE m_cachedStartPosition_player2;

		void InitializePlayer( const SPP & i_player );
		void SetupWalls();
		void OnBallCollideDeadWall( void * i_pInfo );
		bool m_bEnd;
		bool m_bPause;
	};
}
