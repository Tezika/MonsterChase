//
//  EnemyManager.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "enemymanager.h"
#include "game.h"
#include <assert.h>

using namespace MonsterChase;

EnemyManager::EnemyManager()
{
	head_ = nullptr;
	rear_ = nullptr;
}

EnemyManager::~EnemyManager()
{
	if (head_ != nullptr)
	{
		this->DestroyAll();
	}
}

Enemy* EnemyManager::CreateEnemy()
{
	char* name = new char[128];
	std::cout << "Please input the enemy name: ";
	std::cin >> name;

	auto ptr = head_;
	while (ptr != nullptr)
	{
		if (ptr->GetName() == name)
		{
			std::cout << "The name '" << name << "' has already exist, please try anthor one." << std::endl;
			return nullptr;
		}
		ptr = ptr->GetNext();
	}
	//The movespeed ranges from 1 ~ 4, health ranges from 4 ~ 7, attack ranges from 1 ~ 4
	auto newEnemy = this->InsertEnemy(new Enemy(name, rand() % 5 + 3, rand() % 3 + 4, rand() % 3 + 1));
	//Set the random position for the new enemy
	newEnemy->SetPosition(Point2D(rand() % Game::GetInstance().GetGridWidth() + 1, rand() % Game::GetInstance().GetGridHeight() + 1));
	return newEnemy;
}

Enemy* EnemyManager::GetEnemyByName(const char* name)
{
	assert(name != nullptr);
	auto ptr = head_;
	while (ptr != nullptr)
	{
		if (ptr->GetName() == name)
		{
			return ptr;
		}
		ptr = ptr->GetNext();
	}
	return nullptr;
}

Enemy* EnemyManager::InsertEnemy(Enemy* node)
{
	assert(node != nullptr);
	//Insert the first node
	if (head_ == nullptr)
	{
		head_ = node;
		rear_ = node;
	}
	else
	{
		rear_->SetNext(node);
		rear_ = node;
	}
	return node;
}

void EnemyManager::PrintAllEnemiesInfo()
{
	auto ptr = head_;
	while (ptr != nullptr)
	{
		ptr->PrintOutInfo();
		ptr = ptr->GetNext();
	}
}

void EnemyManager::MoveEnemies()
{
	auto ptr = head_;
	while (ptr != nullptr)
	{
		ptr->Move();
		ptr->PrintOutInfo();
		ptr = ptr->GetNext();
	}
}

void EnemyManager::BattleWithPlayer(Player *player)
{
	assert(player != nullptr);
	auto ptr = head_;
	while (ptr != nullptr)
	{
		if (ptr->GetPosition() == player->GetPosition())
		{
			player->SetHealth(player->GetHealth() - ptr->GetAttack());
			std::cout << "The player got a damage by " << ptr->GetAttack() << std::endl;
			if (player->GetHealth() <= 0)
			{
				std::cout << "The player has already died :<." << std::endl;
				Game::GetInstance().TriggerEnd();
				break;
			}
		}
		ptr = ptr->GetNext();
	}
}

void EnemyManager::RemoveDiedEnemy()
{
	Enemy* ptr = head_;
	Enemy* ptr_previous = nullptr;
	while (ptr != nullptr)
	{
		//if the enemy's hp is 0
		if (ptr->GetHealth() == 0)
		{
			std::cout << "The " << ptr->GetName() << " died by its health is 0. " << std::endl;
			if (ptr_previous == nullptr)
			{
				head_ = head_->GetNext();
				delete ptr;
				ptr = head_;
			}
			else
			{
				ptr_previous->SetNext(ptr->GetNext());
				delete ptr;
				ptr = ptr_previous->GetNext();
			}
		}
		else
		{
			ptr_previous = ptr;
			ptr = ptr->GetNext();
		}
	}
}

bool EnemyManager::DestroyAll()
{
	auto ptr = head_;
	while (ptr != nullptr)
	{
		auto curEnemy = ptr;
		ptr = ptr->GetNext();
		delete curEnemy;
	}
	head_ = nullptr;
	rear_ = nullptr;
	return true;
}