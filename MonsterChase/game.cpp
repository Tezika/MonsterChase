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

namespace MonsterChase
{
	void TestKeyCallback( unsigned int i_VKeyID, bool bWentDown )
	{
#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		sprintf_s( Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up" );
		OutputDebugStringA( Buffer );
#endif // __DEBUG
	}

	Game::Game()
		:m_grid_Width( 32 ),
		m_grid_Height( 32 ),
		m_bEnd( false ),
		m_roundTimer_newEnemy( 0 )
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
		GLibSprite * testSprite = Engine::CreateSprite( "Data\\GoodGuy.dds" );
		m_pPlayer->SetSprite( testSprite );
		m_pPlayer->SetSpritePosition( GLibPoint2D{ -180,-100 } );
		DEBUG_PRINT( "----------Finish the setup for the game.----------" );
		return true;
	}

	void Game::Run()
	{
		do
		{
			GLib::SetKeyStateChangeCallback( TestKeyCallback );
			GLib::Service( m_bEnd );
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();
			// Rendering the player for test
			GLibSprite * pPlayerSprite = m_pPlayer->GetSprite();
			if ( pPlayerSprite != nullptr )
			{
				GLib::Sprites::RenderSprite( *pPlayerSprite, m_pPlayer->GetSpritePosition(), 0 );
			}
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		} while ( !m_bEnd );
	}

	void Game::Destroy()
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
		// When the game stops, it should shut down the GLib.
		GLib::Shutdown();
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