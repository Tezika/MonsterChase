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
#include "MessageSystem.h"

extern float Engine::Timing::GetLastFrameTime();
extern FinalProject::SPG Engine::CreateGameObjectByFile( const char * pFileName );

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

		// Create the two players
		m_player_1 = SPP( Engine::CreateGameObjectByFile( "Data\\Lua\\player_1.lua" ) );
		m_player_2 = SPP( Engine::CreateGameObjectByFile( "Data\\Lua\\player_2.lua" ) );
		this->InitializePlayer( m_player_1 );
		this->InitializePlayer( m_player_2 );
		// Cache the player's start position for further use.
		m_cachedStartPosition_player1 = m_player_1->GetPosition();
		m_cachedStartPosition_player2 = m_player_2->GetPosition();

		// Create the ball
		m_ball = SPB( Engine::CreateGameObjectByFile( "Data\\Lua\\ball.lua" ) );

		// Set up Walls
		this->SetupWalls();

		// Register some game element events
		this->m_dBallCollideDeadWall = DEL::Create<Game, &Game::OnBallCollideDeadWall>( this );
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
			// Update the controllers
			Controller::ControllerManager::GetInstance().Update( dt );
			// Update the physics system
			Physics::PhysicsManager::GetInstance().Simulate( dt );
			// Update the rendering system
			Render::RenderManager::GetInstance().Update( dt, m_bEnd );
		} while (!m_bEnd);
	}

	void Game::Reset()
	{
		// Close the controllers
		m_player_1->GetController()->SetEnable( false );
		m_player_2->GetController()->SetEnable( false );

		// Reset the player's velocity abd position
		m_player_1->SetVelocity( VEC3SEE{ 0,0,0 } );
		m_player_2->SetVelocity( VEC3SEE{ 0,0,0 } );

		m_player_1->SetPosition( m_cachedStartPosition_player1 );
		m_player_2->SetPosition( m_cachedStartPosition_player2 );

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
		DEBUG_PRINT_GAMEPLAY( "----------Shutdown the game successfully.----------" );
	}

	void Game::Restart()
	{
		if (m_ball == nullptr)
		{
			return;
		}
		// Open the controllers
		m_player_1->GetController()->SetEnable( true );
		m_player_2->GetController()->SetEnable( true );
		m_ball->Shoot();
		DEBUG_PRINT_GAMEPLAY( "----------Reset the game successfully.----------" );
	}

	void Game::InitializePlayer( const SPP & i_player )
	{
		using namespace Engine;
		// This is a magic number decided by tweaking.
		const float drivingForce = 30.0f;
		// For controller: Create an input controller and assign it to the player.
		InputController * pInputController = new InputController( i_player, drivingForce );
		pInputController->SetControlGameObject( i_player );
		i_player->SetController( pInputController );
		Controller::ControllerManager::GetInstance().AddContrller( pInputController );
	}

	void Game::SetupWalls()
	{
		// Create the wall based on the lua files.
		m_wall_bottom = SPW( Engine::CreateGameObjectByFile( "Data\\Lua\\wall_bottom.lua" ) );
		m_wall_up = SPW( Engine::CreateGameObjectByFile( "Data\\Lua\\wall_up.lua" ) );
		m_wall_right = SPW( Engine::CreateGameObjectByFile( "Data\\Lua\\wall_right.lua" ) );
		m_wall_left = SPW( Engine::CreateGameObjectByFile( "Data\\Lua\\wall_left.lua" ) );
		// Set the left and right wall as the dead walls.
		m_wall_left->SetDead();
		m_wall_right->SetDead();
	}

	void Game::OnBallCollideDeadWall( void * i_pInfo )
	{
		DEBUG_PRINT_GAMEPLAY( "----------Since the ball collided the dead wall, reset the game right now .----------" );
		this->Reset();
	}
}