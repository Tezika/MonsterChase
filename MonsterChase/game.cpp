//
//  game.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#include "game.h"
#include <ctime>

using namespace MonsterChase;

Game::Game()
{
	m_Grid_Width_ = 32;
	m_Grid_Height_ = 32;
	m_bBool_ = false;
	m_roundTimer_newEnemy_ = 0;
}

void Game::Initialize()
{
	std::cout << "----------Setup Begin----------" << std::endl;
	srand(time_t(NULL));
	//Player initialization
	char* playerName = new char[128];
	std::cout << "what's your name? ";
	std::cin >> playerName;
	m_pPlayer_ = new Player(playerName, 1, 15);
	//Place the player in [1,1]
	player_->SetPosition(Point2D<int>(1, 1));

	//Enemy initialization
	int num_enemy = 0;
	std::cout << "Hi " << playerName << "! How many enemy do you want to fight with? ";
	std::cin >> num_enemy;

	m_pEnemyManager_ = new EnemyManager();
	while (num_enemy != 0)
	{
		auto enemy = m_pEnemyManager_->CreateEnemy();
		if (enemy != nullptr)
		{
			num_enemy--;
			enemy->PrintOutInfo();
		}
	}
	std::cout << "----------Setup End-----------" << std::endl;
	delete playerName;
}

void Game::Run()
{
	std::cout << "----------A Round Start-----------" << std::endl;
	//Create new enemy every six rounds
	if (++m_roundTimer_newEnemy_ == 6)
	{
		std::cout << "Now creating a new enemy occasionally." << std::endl;
		m_roundTimer_newEnemy_ = 0;
		auto enemy = m_pEnemyManager_->CreateEnemy();
		if (enemy != nullptr)
		{
			enemy->PrintOutInfo();
		}
	}
	//Move the player firstly.
	m_pPlayer_->Move();
	m_pPlayer_->PrintOutInfo();

	m_pEnemyManager_->MoveEnemies();
	m_pEnemyManager_->RemoveDiedEnemy();

	m_pEnemyManager_->BattleWithPlayer(m_pPlayer_);
	std::cout << "----------The Round End-------------" << std::endl;
}

void Game::Stop()
{
	std::cout << "Your will quit the game :)" << std::endl;
	delete m_pEnemyManager_;
	m_pEnemyManager_ = nullptr;
	delete m_pPlayer_;
	m_pPlayer_ = nullptr;
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
