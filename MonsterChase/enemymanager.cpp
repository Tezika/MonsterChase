//
//  EnemyManager.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//
#include <iostream>
#include <math.h>
#include <assert.h>
#include "Allocator.h"
#include "AIController.h"
#include "enemymanager.h"
#include "game.h"
#include "SubSystems.h"


using namespace Engine;

namespace MonsterChase
{
	EnemyManager::EnemyManager()
		:m_pEnemyList( new TRACK_NEW TList<Enemy>() )
	{
	}

	EnemyManager::~EnemyManager()
	{
	}

	Enemy * EnemyManager::CreateEnemy()
	{
		TString name;
		std::cout << "Please input the enemy name: ";
		std::cin >> name;

		auto ptr = m_pEnemyList->GetHead();
		while ( ptr != nullptr )
		{
			if ( ptr->GetData()->GetName() == name )
			{
				std::cout << "The name '" << name << "' has already exist, please try anthor one." << std::endl;
				return nullptr;
			}
			ptr = ptr->GetNext();
		}
		// The ranges from 4 ~ 7, attack ranges from 1 ~ 4
		// Setup the random position for the new enemy
		Node<Enemy> * pNewEnemyNode = m_pEnemyList->InsertToTail( new Enemy(
			name,
			Point2D<float>( static_cast<float>( rand() % Game::GetInstance().GetGridWidth() + 1 ), static_cast<float>( rand() % Game::GetInstance().GetGridHeight() + 1 ) ),
			rand() % 3 + 4,
			rand() % 3 + 1
		) );
		SmartPtr<Enemy> pNewEnemy = SmartPtr<Enemy>( pNewEnemyNode->GetData() );;
		AIController * newController = new AIController();
		newController->SetControlGameObject( pNewEnemy );
		newController->SetPlayer( Game::GetInstance().GetCurPlayer() );
		newController->SetMoveSpeed( rand() % 3 + 1 );
		pNewEnemy->SetController( newController );

		// Add the controller into Controller Manager
		Controller::ControllerManager::GetInstance().AddContrller( newController );

		// Create new RenderInfo for the enemy
		Render::RenderManager::GetInstance().AddRenderObject( pNewEnemy, "Data\\BadGuy.dds" );
		// Create new PhysicsInfo for the enemy 
		Physics::PhysicsInfo * pEnemyPhysicsInfo = Physics::PhysicsInfo::Create( 1.0, 0.005f, pNewEnemy );
		// Add an initial force to the enemy
		pEnemyPhysicsInfo->SetDrivingForce( Point2D<float>( 300, 0 ) );
		Physics::PhysicsManager::GetInstance().AddPhysicsObject( pEnemyPhysicsInfo );
		return pNewEnemyNode->GetData();
	}

	Enemy * EnemyManager::GetEnemyByName( const char * name )
	{
		assert( name != nullptr );

		auto ptr = m_pEnemyList->GetHead();
		while ( ptr != nullptr )
		{
			Enemy * pEnemy = ptr->GetData();
			if ( pEnemy->GetName() == name )
			{
				return pEnemy;
			}
			ptr = ptr->GetNext();
		}
		return nullptr;
	}

	Enemy * EnemyManager::InsertEnemy( Enemy * node )
	{
		assert( node != nullptr );
		//Insert the first node
		m_pEnemyList->InsertToTail( node );
		return node;
	}

	void EnemyManager::PrintAllEnemiesInfo()
	{
		auto ptr = m_pEnemyList->GetHead();
		while ( ptr != nullptr )
		{
			ptr->GetData()->PrintOutInfo();
			ptr = ptr->GetNext();
		}
	}

	void EnemyManager::MoveEnemies()
	{
		auto ptr = m_pEnemyList->GetHead();
		Enemy * pEnemy = nullptr;
		while ( ptr != nullptr )
		{
			pEnemy = ptr->GetData();
			pEnemy->PrintOutInfo();
			ptr = ptr->GetNext();
		}
	}

	void EnemyManager::BattleWithPlayer( Player * player )
	{
		assert( player != nullptr );
		auto ptr = m_pEnemyList->GetHead();
		Enemy * pEnemy = nullptr;
		while ( ptr != nullptr )
		{
			pEnemy = ptr->GetData();
			if ( pEnemy->GetPosition() == player->GetPosition() )
			{
				player->SetHealth( player->GetHealth() - pEnemy->GetAttack() );
				std::cout << "The player got a damage by " << pEnemy->GetAttack() << std::endl;
				if ( player->GetHealth() <= 0 )
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
		auto ptr = m_pEnemyList->GetHead();
		Enemy * pEnemy = nullptr;
		while ( ptr != nullptr )
		{
			pEnemy = ptr->GetData();
			if ( pEnemy->GetHealth() == 0 )
			{
				Enemy * pRemoveEnemy = pEnemy;
				std::cout << "The " << pRemoveEnemy->GetName() << " died by its health is 0" << std::endl;
				ptr = m_pEnemyList->Remove( ptr );
				delete pRemoveEnemy;
			}
			else
			{
				ptr = ptr->GetNext();
			}
		}
	}
}
