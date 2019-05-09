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

namespace FinalProject
{
	Game::Game()
		:m_bEnd( false )
	{
	}

	bool Game::Initialize()
	{
		using namespace Engine;
		DEBUG_PRINT_GAMEPLAY( "----------Begin the setup for the game.----------" );
		srand( time_t( NULL ) );

		// Test for lua file
		m_player_1 = SmartPtr<Player>( Engine::CreateGameObjectByFile( "Data\\Lua\\player_1.lua" ) );
		//m_player_2 = SmartPtr<Player>( Engine::CreateGameObjectByFile( "Data\\Lua\\player_2.lua" ) );
		// Create an input controller and assign it to the player.
		InputController * pInputController = new InputController( m_player_1, 40000 );
		pInputController->SetControlGameObject( m_player_1 );
		m_player_1->SetController( pInputController );
		Controller::ControllerManager::GetInstance().AddContrller( pInputController );

		// Create some test enemies by lua.

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
		m_player_1 = nullptr;
		m_player_2 = nullptr;
		DEBUG_PRINT_GAMEPLAY( "----------Shutdown the game successfully.----------" );
	}
}