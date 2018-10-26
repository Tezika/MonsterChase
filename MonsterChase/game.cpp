//
//  game.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include "game.h"
#include <ctime>

using namespace MonsterChase;

Game::Game()
{
	grid_width_ = 32;
	grid_height_ = 32;
	end_ = false;
	roundTimer_newEnemy_ = 0;
}

void Game::Initialize()
{
	std::cout << "----------Setup Begin----------" << std::endl;
	srand(time_t(NULL));
	//Player initialization
	char* playerName = new char[128];
	std::cout << "what's your name? ";
	std::cin >> playerName;
	player_ = new Player(playerName, 1, 15);
	//Place the player in [1,1]
	player_->SetPosition(Point2D<int>(1, 1));

	//Enemy initialization
	int num_enemy = 0;
	std::cout << "Hi " << playerName << "! How many enemy do you want to fight with? ";
	std::cin >> num_enemy;

	enemyManager_ = new EnemyManager();
	while (num_enemy != 0)
	{
		auto enemy = enemyManager_->CreateEnemy();
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
	if (++roundTimer_newEnemy_ == 6)
	{
		std::cout << "Now creating a new enemy occasionally." << std::endl;
		roundTimer_newEnemy_ = 0;
		auto enemy = enemyManager_->CreateEnemy();
		if (enemy != nullptr)
		{
			enemy->PrintOutInfo();
		}
	}
	//Move the player firstly.
	player_->Move();
	player_->PrintOutInfo();

	enemyManager_->MoveEnemies();
	enemyManager_->RemoveDiedEnemy();

	enemyManager_->BattleWithPlayer(player_);
	std::cout << "----------The Round End-------------" << std::endl;
}

void Game::Stop()
{
	std::cout << "Your will quit the game :)" << std::endl;
	delete enemyManager_;
	enemyManager_ = nullptr;
	delete player_;
	player_ = nullptr;
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
