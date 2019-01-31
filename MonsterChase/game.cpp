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
#include "RenderManager.h"

extern float Timing::GetLastFrameTime();

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
		DEBUG_PRINT( "----------Begin the setup for the game.----------" );
		srand( time_t( NULL ) );
		// Initialize the GLib.
		bool bSuccess = GLib::Initialize( i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600 );
		if ( !bSuccess )
		{
			return bSuccess;
		}
		// Initialize the player
		m_pPlayer = new TRACK_NEW Player( "Tezika", Point2D<int>( 1, 1 ), 15 );
		m_pPlayer->SetController( nullptr );
		Render::RenderManager::GetInstance().AddRenderObject( m_pPlayer, "Data\\GoodGuy.dds" );

		// Initialize the test enemies
		m_pEnemyManager->CreateEnemy();
		m_pEnemyManager->CreateEnemy();

		DEBUG_PRINT( "----------Finish the setup for the game.----------" );
		return true;
	}

	void Game::Run()
	{
		do
		{
			float dt = Timing::GetLastFrameTime();
			// Update the physics
			// Update the rendering
			Render::RenderManager::GetInstance().Update( dt, m_bEnd );
		} while ( !m_bEnd );
	}

	void Game::Destroy()
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
		DEBUG_PRINT( "----------Shutdown the game successfully.----------" );
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