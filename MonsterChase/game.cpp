//
//  game.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#include "game.h"
#include <ctime>

namespace MonsterChase
{
	Game::Game()
		:m_grid_Width(32),
		m_grid_Height(32),
		m_bEnd(false),
		m_roundTimer_newEnemy(0)
	{
	}

	void Game::Initialize()
	{
		std::cout << "----------Setup Begin----------" << std::endl;
		srand(time_t(NULL));
		//Player initialization
		TString playerName;
		std::cout << "what's your name? ";
		std::cin >> playerName;
		m_pPlayer = new Player(playerName, 1, 15);
		//Place the player in [1,1]
		m_pPlayer->SetPosition(Point2D<int>(1, 1));

		//Enemy initialization
		int num_enemy = 0;
		std::cout << "Hi " << playerName << "! How many enemy do you want to fight with? ";
		std::cin >> num_enemy;

		m_pEnemyManager = new EnemyManager();
		while (num_enemy != 0)
		{
			auto enemy = m_pEnemyManager->CreateEnemy();
			if (enemy != nullptr)
			{
				num_enemy--;
				enemy->PrintOutInfo();
			}
		}
		std::cout << "----------Setup End-----------" << std::endl;
	}

	void Game::Run()
	{
		std::cout << "----------A Round Start-----------" << std::endl;
		//Create new enemy every six rounds
		if (++m_roundTimer_newEnemy == 6)
		{
			std::cout << "Now creating a new enemy occasionally." << std::endl;
			m_roundTimer_newEnemy = 0;
			auto enemy = m_pEnemyManager->CreateEnemy();
			if (enemy != nullptr)
			{
				enemy->PrintOutInfo();
			}
		}
		//Move the player firstly.
		m_pPlayer->Move();
		m_pPlayer->PrintOutInfo();

		m_pEnemyManager->MoveEnemies();
		m_pEnemyManager->RemoveDiedEnemy();

		m_pEnemyManager->BattleWithPlayer(m_pPlayer);
		std::cout << "----------The Round End-------------" << std::endl;
	}

	void Game::Stop()
	{
		std::cout << "Your will quit the game :)" << std::endl;
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
		delete m_pPlayer;
		m_pPlayer = nullptr;
		_CrtDumpMemoryLeaks();
	}

	int Game::ClampForMap(int val, int maxiumVal)
	{
		if (val <= 0)
		{
			return 1;
		}
		else if (val > maxiumVal)
		{
			return maxiumVal;
		}
		return val;
	}

}
