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
#include "Windows.h"
#include "SmartPtr.h"

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

		Game( Game const & ) = delete;
		Game & operator=( Game const & ) = delete;

	private:
		Game();

	public:
		bool Initialize();
		void Run();
		void Destroy();

		bool ShouldEnd() { return m_bEnd; }
		void TriggerEnd() { m_bEnd = true; }
		Engine::SmartPtr<Engine::GameObject> GetCurPlayer() { return m_pPlayer; }

	private:
		Engine::SmartPtr<Engine::GameObject> m_pPlayer;
		bool m_bEnd;
	};
}
