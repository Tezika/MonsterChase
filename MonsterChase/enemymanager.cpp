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
using namespace Engine;

EnemyManager::EnemyManager()
{
	m_pEnemyList_ = new TList<Enemy>();
}

EnemyManager::~EnemyManager()
{
	delete m_pEnemyList_;
}

Enemy* EnemyManager::CreateEnemy()
{
	char* name = new char[128];
	std::cout << "Please input the enemy name: ";
	std::cin >> name;

	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		if ( ptr->data->GetName() == name )
		{
			std::cout << "The name '" << name << "' has already exist, please try anthor one." << std::endl;
			return nullptr;
		}
		ptr = ptr->next;
	}

	//The movespeed ranges from 1 ~ 4, health ranges from 4 ~ 7, attack ranges from 1 ~ 4
	auto newEnemy = m_pEnemyList_->InsertToTail(new Enemy(name, rand() % 5 + 3, rand() % 3 + 4, rand() % 3 + 1));
	//Set the random position for the new enemy
	newEnemy->data->SetPosition(Point2D(rand() % Game::GetInstance().GetGridWidth() + 1, rand() % Game::GetInstance().GetGridHeight() + 1)); 
	delete name;
	return newEnemy->data;
}

Enemy* EnemyManager::GetEnemyByName(const char* name)
{
	assert(name != nullptr);

	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		if (ptr->data->GetName() == name)
		{
			return ptr->data;
		}
		ptr = ptr->next;
	}
	return nullptr;
}

Enemy* EnemyManager::InsertEnemy(Enemy* node)
{
	assert(node != nullptr);
	//Insert the first node
	m_pEnemyList_->InsertToTail(node);
	return node;
}

void EnemyManager::PrintAllEnemiesInfo()
{
	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		ptr->data->PrintOutInfo();
		ptr = ptr->next;
	}
}

void EnemyManager::MoveEnemies()
{
	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		ptr->data->Move();
		ptr->data->PrintOutInfo();
		ptr = ptr->next;
	}
}

void EnemyManager::BattleWithPlayer(Player *player)
{
	assert(player != nullptr);
	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		if (ptr->data->GetPosition() == player->GetPosition())
		{
			player->SetHealth(player->GetHealth() - ptr->data->GetAttack());
			std::cout << "The player got a damage by " << ptr->data->GetAttack() << std::endl;
			if (player->GetHealth() <= 0)
			{
				std::cout << "The player has already died :<." << std::endl;
				Game::GetInstance().TriggerEnd();
				break;
			}
		}
		ptr = ptr->next;
	}
}

void EnemyManager::RemoveDiedEnemy()
{
	auto ptr = m_pEnemyList_->head;
	while (ptr != nullptr)
	{
		if (ptr->data->GetHealth() == 0)
		{
			auto enemy = ptr->data;
			std::cout << "The " << ptr->data->GetName() << " died by its health is 0" << std::endl;
			ptr = m_pEnemyList_->Remove(ptr);
			delete enemy;
		}
		else
		{
			ptr = ptr->next;
		}
	}
}
