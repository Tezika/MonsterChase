#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include "game.h"
#include "GLib.h"
#include "PhysicsManager.h"
#include "Vector3.h"
#include "Vector3SSE.h"
#include "ConsolePrint.h"
#include <iostream>

namespace TPong
{
	void InputCallback( unsigned int i_VKeyID, bool bWentDown )
	{
		using namespace Engine;
		// Access the current player's controller.
		static InputController * pCurrentController = nullptr;
		static Physics::PhysicsInfo * pCachedPhysicsInfo = nullptr;
		static Vector3 cachedDrivingForce = Vector3::Zero;
		bool bApplyForce = true;
		if ( bWentDown )
		{
			// Maybe need to encapsulate a little bit better.
			// If I want to make it support the arrow keys, I need to modify the input.cpp from GLib.
			switch ( i_VKeyID )
			{
				// For W
			case 0x57:
				pCurrentController = static_cast< InputController * >(Game::GetInstance().GetPlayer1()->GetController());
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of up for player 1" );
				break;
				// For S
			case 0x53:
				pCurrentController = static_cast< InputController * >(Game::GetInstance().GetPlayer1()->GetController());
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = -pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of down for player 1" );
				break;
				// For O
			case 0x4F:
				pCurrentController = static_cast< InputController * >(Game::GetInstance().GetPlayer2()->GetController());
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of up for player 2" );
				break;
				// For K
			case 0x4B:
				pCurrentController = static_cast< InputController * >(Game::GetInstance().GetPlayer2()->GetController());
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = -pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of down for player 2" );
				break;
				// For space bar
			case 0x20:
				bApplyForce = false;
				Game::GetInstance().Restart();
				break;
				// For the enter key
			case 0x0D:
				bApplyForce = false;
				Game::GetInstance().TooglePause();
				break;
			default:
				bApplyForce = false;
				break;
			}
		}
		else
		{
			bApplyForce = false;
			cachedDrivingForce.x = 0;
			cachedDrivingForce.y = 0;
			DEBUG_PRINT_GAMEPLAY( "Stop applying the force right now!" );
		}
		if ( !bApplyForce )
		{
			return;
		}
		// If the controller is not available right now, 
		if ( !pCurrentController->IsEnable() )
		{
			return;
		}
		// Get the associated PhysicsInfo.
		pCachedPhysicsInfo = pCurrentController->GetPhysicsInfo();
		// Apply the force to GameObject.
		pCachedPhysicsInfo->SetDrivingForce( Vector3SSE{ cachedDrivingForce.x, cachedDrivingForce.y, cachedDrivingForce.z } );
	}

	InputController::InputController() :
		m_pCachedPhysicsInfo( nullptr ),
		m_pControlObject( nullptr ),
		m_drivingForce( 20.0f )
	{
		GLib::SetKeyStateChangeCallback( InputCallback );
	}

	InputController::InputController( Engine::SmartPtr<Engine::GameObject> i_pGo, float i_drivingForce ) :
		m_pCachedPhysicsInfo( nullptr ),
		m_pControlObject( i_pGo ),
		m_drivingForce( i_drivingForce )
	{
		GLib::SetKeyStateChangeCallback( InputCallback );
	}

	InputController::~InputController()
	{
	}

	void InputController::UpdateGameObject( float i_dt )
	{
		if ( !m_bIsEnable )
		{
			return;
		}
	}

	void InputController::SetEnable( bool isEnable )
	{
		m_bIsEnable = isEnable;
		if ( !m_bIsEnable )
		{
			this->GetPhysicsInfo()->SetDrivingForce( Engine::Vector3SSE{ 0,0,0 } );
		}
	}

	Engine::Physics::PhysicsInfo * InputController::GetPhysicsInfo()
	{
		if ( m_pCachedPhysicsInfo == nullptr )
		{
			m_pCachedPhysicsInfo = Engine::Physics::PhysicsManager::GetInstance().GetInfoByGameObject( m_pControlObject );
		}
		return m_pCachedPhysicsInfo;
	}
}