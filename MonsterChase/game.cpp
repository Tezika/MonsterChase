//
//  game.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//
#include "stdafx.h"
#include "game.h"
#include "InputController.h"
#include "GLibUtility.h"
#include <ctime>
#include "Timer.h"
#include "SubSystems.h"
#include "LuaParser.h"
#include "ConsolePrint.h"

extern float Engine::Timing::GetLastFrameTime();
extern Engine::SmartPtr<Engine::GameObject> Engine::CreateGameObjectByFile( const char * pFileName );

namespace MonsterChase
{
	Game::Game()
		:m_bEnd( false )
	{
	}

	bool Game::Initialize()
	{
		DEBUG_PRINT_GAMEPLAY( "----------Begin the setup for the game.----------" );
		srand( time_t( NULL ) );

		// Test for lua file
		//m_pPlayer = Engine::CreateGameObjectByFile( "Data\\Lua\\player.lua" );
		//// Create an input controller and assign it to the player.
		//InputController * pInputController = new InputController( m_pPlayer, 2000.0f );
		//pInputController->SetControlGameObject( m_pPlayer );
		//m_pPlayer->SetController( pInputController );
		//Controller::ControllerManager::GetInstance().AddContrller( pInputController );

		// Create some test enemies by lua.
		Engine::CreateGameObjectByFile( "Data\\lua\\player.lua" );
		Engine::CreateGameObjectByFile( "Data\\lua\\test_enemy.lua" );
		Engine::CreateGameObjectByFile( "Data\\lua\\test_enemy_1.lua" );
		Engine::CreateGameObjectByFile( "Data\\lua\\test_enemy_2.lua" );
		Engine::CreateGameObjectByFile( "Data\\lua\\test_enemy_3.lua" );
		Engine::CreateGameObjectByFile( "Data\\lua\\test_enemy_4.lua" );

		DEBUG_PRINT_GAMEPLAY( "----------Finish the setup for the game.----------" );
		return true;
	}

	void Game::Run()
	{
		using namespace Engine;
		do
		{
			float dt = Engine::Timing::GetLastFrameTime();
			// Update the controllers
			Controller::ControllerManager::GetInstance().Update( dt );
			// Update the physics system
			Physics::PhysicsManager::GetInstance().Simulate( dt );
			// Update the rendering system
			Render::RenderManager::GetInstance().Update( dt, m_bEnd );
		} while ( !m_bEnd );
	}

	void Game::Destroy()
	{
		m_pPlayer = nullptr;
		DEBUG_PRINT_GAMEPLAY( "----------Shutdown the game successfully.----------" );
	}
}