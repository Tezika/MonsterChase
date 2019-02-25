//
//  game.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#include "game.h"
#include "Allocator.h"
#include "InputController.h"
#include "AIController.h"
#include "GLibUtility.h"
#include <ctime>
#include "Timer.h"
#include "SubSystems.h"
#include "LuaParser.h"

extern float Timing::GetLastFrameTime();
extern SmartPtr<GameObject> Engine::CreateGameObjectByFile( const char * pFileName );

namespace MonsterChase
{
	Game::Game()
		:m_grid_Width( 32 ),
		m_grid_Height( 32 ),
		m_bEnd( false ),
		m_roundTimer_newEnemy( 0 ),
		m_pEnemyManager( new EnemyManager() )
	{
	}

	bool Game::Initialize( HINSTANCE i_hInstance, int i_nCmdShow )
	{
		DEBUG_PRINT_GAMEPLAY( "----------Begin the setup for the game.----------" );
		srand( time_t( NULL ) );
		// Initialize the GLib.
		bool bSuccess = GLib::Initialize( i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600 );
		if ( !bSuccess )
		{
			return bSuccess;
		}

		// Test for lua file
		m_pPlayer = Engine::CreateGameObjectByFile( "Data\\Lua\\player.lua" );
		// Create an input controller and assign it to the player.
		InputController * pInputController = new InputController( m_pPlayer, 2000.0f );
		pInputController->SetControlGameObject( m_pPlayer );
		m_pPlayer->SetController( pInputController );

		// Initialize the test enemies
		m_pEnemyManager->CreateEnemy();


		DEBUG_PRINT_GAMEPLAY( "----------Finish the setup for the game.----------" );
		return true;
	}

	void Game::Run()
	{
		do
		{
			float dt = Timing::GetLastFrameTime();
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
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
		DEBUG_PRINT_GAMEPLAY( "----------Shutdown the game successfully.----------" );
	}

	int Game::ClampForMap( int val, int maxiumVal )
	{
		if ( val <= 0 )
		{
			return 1;
		}
		else if ( val > maxiumVal )
		{
			return maxiumVal;
		}
		return val;
	}
}