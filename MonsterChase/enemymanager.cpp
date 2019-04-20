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
#include "AIController.h"
#include "enemymanager.h"
#include "game.h"
#include "SubSystems.h"
#include "LuaParser.h"


using namespace Engine;
extern SmartPtr<GameObject> Engine::CreateGameObjectByFile( const char * pFileName );

namespace MonsterChase
{
	EnemyManager::EnemyManager()
	{
	}

	EnemyManager::~EnemyManager()
	{
	}


	SmartPtr<GameObject> EnemyManager::CreateEnemy( const char * i_pFileName )
	{
		assert( i_pFileName );
		SmartPtr<GameObject> pNewEnemy = Engine::CreateGameObjectByFile( i_pFileName );
		AIController * pNewController = new AIController();
		pNewController->SetControlGameObject( pNewEnemy );
		pNewController->SetPlayer( Game::GetInstance().GetCurPlayer() );
		pNewController->SetMoveSpeed( rand() % 3 + 1 );
		pNewEnemy->SetController( pNewController );
		Controller::ControllerManager::GetInstance().AddContrller( pNewController );

		return pNewEnemy;
	}
}