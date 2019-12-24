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
#include "SubSystemHeaders.h"
#include "LuaParser.h"
#include "ConsolePrint.h"
#include "MessageSystem.h"

extern float Engine::Timing::GetLastFrameTime();
extern TPong::SPG Engine::CreateGameObjectByFile( const char* pFileName );

namespace
{
	void CreateWall( const char* i_filePath, Engine::SmartPtr<TPong::Wall>& o_wall )
	{
		auto go_temp = Engine::CreateGameObjectByFile( i_filePath );
		if (go_temp == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the wall's lua file." );
		}
		o_wall->SetGameObject( go_temp );
	}
}
namespace TPong
{
	Game::Game()
		:m_bEnd( false ), m_bPause( false )
	{
	}

	bool Game::Initialize()
	{
		using namespace Engine;
		DEBUG_PRINT_GAMEPLAY( "----------Begin the setup for the game.----------" );
		srand( time_t( NULL ) );

		// Create the two players
		auto go_player_1 = Engine::CreateGameObjectByFile( "Content\\Lua\\player_1.lua" );
		if (go_player_1 == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the player one lua file." );
			return false;
		}
		m_player_1->SetGameObject( go_player_1 );
		this->InitializePlayer( m_player_1 );
		auto go_player_2 = Engine::CreateGameObjectByFile( "Content\\Lua\\player_2.lua" );
		if (go_player_2 == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the player two lua file." );
			return false;
		}
		m_player_2->SetGameObject( go_player_2 );
		this->InitializePlayer( m_player_2 );

		// Cache the player's start position for further use.
		m_cachedStartPosition_player1 = go_player_1->GetPosition();
		m_cachedStartPosition_player2 = go_player_2->GetPosition();

		// Create the ball
		auto go_ball = Engine::CreateGameObjectByFile( "Content\\Lua\\ball.lua" );
		if (go_ball == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the ball lua file." );
			return false;
		}
		m_ball->SetGameObject( go_ball );

		// Create the sound
		m_bgm = Audio::Sound::sSoundSource::Create( "Content\\Sound\\bgm.wav" );
		if (m_bgm == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the bgm." );
		}
		m_bgmChannelId = m_bgm->Play();

		// Set up Walls
		this->SetupWalls();

		// Register some game element events
		this->m_dBallCollideDeadWall = DEL::Create<Game, & Game::OnBallCollideDeadWall>( this );
		Messaging::MessageSystem::GetInstance().RegisterMessageDelegate( "OnBallCollideDeadWall", this->m_dBallCollideDeadWall );

		// Reset the game at first
		this->Reset();

		DEBUG_PRINT_GAMEPLAY( "----------Finish the setup for the game.----------" );
		return true;
	}

	void Game::Run()
	{
		using namespace Engine;
		do
		{
			float dt = Engine::Timing::GetLastFrameTime();
			if (!m_bPause)
			{
				// Update the controllers
				Controller::ControllerManager::GetInstance().Update( dt );
				// Update the physics system
				Physics::PhysicsManager::GetInstance().Simulate( dt );
			}
			// Update the rendering system anyway
			Render::RenderManager::GetInstance().Update( dt, m_bEnd );
		} while (!m_bEnd);
	}

	void Game::Reset()
	{
		auto go_player_1 = m_player_1->GetGameObject();
		auto go_player_2 = m_player_2->GetGameObject();
		// Close the controllers
		go_player_1->GetController()->SetEnable( false );
		go_player_2->GetController()->SetEnable( false );

		// Reset the player's velocity abd position
		go_player_1->SetVelocity( VEC3SEE{ 0,0,0 } );
		go_player_2->SetVelocity( VEC3SEE{ 0,0,0 } );

		go_player_1->SetPosition( m_cachedStartPosition_player1 );
		go_player_2->SetPosition( m_cachedStartPosition_player2 );

		//Reset the ball
		m_ball->Reset();
	}

	void Game::Destroy()
	{
		using namespace Engine;
		// Deregister events
		Messaging::MessageSystem::GetInstance().DeregisterMessageDelegate( "OnBallCollideDeadWall", this->m_dBallCollideDeadWall );
		// Reassign to nullptr to prevent the memory leak
		m_player_1 = nullptr;
		m_player_2 = nullptr;
		m_ball = nullptr;
		m_wall_bottom = nullptr;
		m_wall_up = nullptr;
		m_wall_left = nullptr;
		m_wall_right = nullptr;
		if (m_bgm != nullptr)
		{
			m_bgm->Stop( m_bgmChannelId );
		}
		m_bgm = nullptr;
		DEBUG_PRINT_GAMEPLAY( "----------Shutdown the game successfully.----------" );
	}

	void Game::Restart()
	{
		if (m_ball == nullptr || m_bPause)
		{
			return;
		}
		// Open the controllers
		m_player_1->GetGameObject()->GetController()->SetEnable( true );
		m_player_2->GetGameObject()->GetController()->SetEnable( true );
		m_ball->Shoot();
		DEBUG_PRINT_GAMEPLAY( "----------Reset the game successfully.----------" );
	}

	void Game::InitializePlayer( const SPP& i_player )
	{
		using namespace Engine;
		// This is a magic number decided by tweaking.
		const float drivingForce = 600.0f;
		// For controller: Create an input controller and assign it to the player.
		InputController* pInputController = new InputController( i_player, drivingForce );
		pInputController->SetControlGameObject( i_player );
		i_player->GetGameObject()->SetController( pInputController );
		Controller::ControllerManager::GetInstance().AddContrller( pInputController );
	}

	void Game::SetupWalls()
	{
		CreateWall( "Content\\Lua\\wall_bottom.lua", m_wall_bottom );
		CreateWall( "Content\\Lua\\wall_up.lua", m_wall_up );
		CreateWall( "Content\\Lua\\wall_right.lua", m_wall_right );
		CreateWall( "Content\\Lua\\wall_left.lua", m_wall_left );
		// Set the left and right wall as the dead walls.
		m_wall_left->SetDead();
		m_wall_right->SetDead();
	}

	void Game::OnBallCollideDeadWall( void* i_pInfo )
	{
		DEBUG_PRINT_GAMEPLAY( "----------Since the ball collided the dead wall, reset the game right now .----------" );
		this->Reset();
	}
}