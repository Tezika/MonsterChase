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


using namespace Engine;

namespace MonsterChase
{
	EnemyManager::EnemyManager()
		:m_pEnemyList(new TList<Enemy>())
	{
	}

	EnemyManager::~EnemyManager()
	{
		delete m_pEnemyList;
	}

	Enemy * EnemyManager::CreateEnemy()
	{
		TString name;
		std::cout << "Please input the enemy name: ";
		std::cin >> name;

		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			if (ptr->m_pData->GetName() == name)
			{
				std::cout << "The name '" << name << "' has already exist, please try anthor one." << std::endl;
				return nullptr;
			}
			ptr = ptr->m_pNext;
		}

		//The movespeed ranges from 1 ~ 4, health ranges from 4 ~ 7, attack ranges from 1 ~ 4
		auto newEnemy = m_pEnemyList->InsertToTail(new Enemy(name, rand() % 5 + 3, rand() % 3 + 4, rand() % 3 + 1));
		//Set the random position for the new enemy
		newEnemy->m_pData->SetPosition(Point2D<int>(rand() % Game::GetInstance().GetGridWidth() + 1, rand() % Game::GetInstance().GetGridHeight() + 1));
		return newEnemy->m_pData;
	}

	Enemy * EnemyManager::GetEnemyByName(const char * name)
	{
		assert(name != nullptr);

		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			if (ptr->m_pData->GetName() == name)
			{
				return ptr->m_pData;
			}
			ptr = ptr->m_pNext;
		}
		return nullptr;
	}

	Enemy * EnemyManager::InsertEnemy(Enemy * node)
	{
		assert(node != nullptr);
		//Insert the first node
		m_pEnemyList->InsertToTail(node);
		return node;
	}

	void EnemyManager::PrintAllEnemiesInfo()
	{
		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			ptr->m_pData->PrintOutInfo();
			ptr = ptr->m_pNext;
		}
	}

	void EnemyManager::MoveEnemies()
	{
		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			ptr->m_pData->Move();
			ptr->m_pData->PrintOutInfo();
			ptr = ptr->m_pNext;
		}
	}

	void EnemyManager::BattleWithPlayer(Player * player)
	{
		assert(player != nullptr);
		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			if (ptr->m_pData->GetPosition() == player->GetPosition())
			{
				player->SetHealth(player->GetHealth() - ptr->m_pData->GetAttack());
				std::cout << "The player got a damage by " << ptr->m_pData->GetAttack() << std::endl;
				if (player->GetHealth() <= 0)
				{
					std::cout << "The player has already died :<." << std::endl;
					Game::GetInstance().TriggerEnd();
					break;
				}
			}
			ptr = ptr->m_pNext;
		}
	}

	void EnemyManager::RemoveDiedEnemy()
	{
		auto ptr = m_pEnemyList->m_pHead;
		while (ptr != nullptr)
		{
			if (ptr->m_pData->GetHealth() == 0)
			{
				auto enemy = ptr->m_pData;
				std::cout << "The " << ptr->m_pData->GetName() << " died by its health is 0" << std::endl;
				ptr = m_pEnemyList->Remove(ptr);
				delete enemy;
			}
			else
			{
				ptr = ptr->m_pNext;
			}
		}
	}
}
