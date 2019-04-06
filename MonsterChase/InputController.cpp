#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include <iostream>
#include "game.h"
#include "GLib.h"
#include "PhysicsManager.h"


namespace MonsterChase
{
	void InputCallback( unsigned int i_VKeyID, bool bWentDown )
	{
		// Access the current player's controller.
		InputController * pCurrentController = static_cast<InputController *>( Game::GetInstance().GetCurPlayer()->GetController() );
		Physics::PhysicsInfo * pCachedPhysicsInfo = pCurrentController->GetPhysicsInfo();
		static Vector3 cachedDrivingForce = Vector3::Zero;
		if ( bWentDown )
		{
			// Maybe need to encapsulate a little bit better.
			// If I want to make it support the arrow keys, I need to modify the input.cpp from GLib.
			switch ( i_VKeyID )
			{
				// For A
			case 0x41:
				cachedDrivingForce.x = -pCurrentController->GetDrivingForce();
				cachedDrivingForce.y = 0;
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of left" );
				break;
				// For W
			case 0x57:
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of up" );
				break;
				// For D
			case 0x44:
				cachedDrivingForce.x = pCurrentController->GetDrivingForce();
				cachedDrivingForce.y = 0;
				DEBUG_PRINT_GAMEPLAY( "Start applying  the force with direction of right" );
				break;
				// For S
			case 0x53:
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = -pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of down" );
				break;
			default:
				break;
			}
		}
		else
		{
			cachedDrivingForce.x = 0;
			cachedDrivingForce.y = 0;
			DEBUG_PRINT_GAMEPLAY( "Stop applying the force right now!" );
		}
		// Apply the force to game object
		pCachedPhysicsInfo->SetDrivingForce( cachedDrivingForce );
	}

	InputController::InputController() :
		m_pCachedPhysicsInfo( nullptr ),
		m_pControlObject( nullptr ),
		m_drivingForce( 300.0f )
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
	}

	Physics::PhysicsInfo * InputController::GetPhysicsInfo()
	{
		if ( m_pCachedPhysicsInfo == nullptr )
		{
			m_pCachedPhysicsInfo = Physics::PhysicsManager::GetInstance().GetInfoByGameObject( m_pControlObject );
		}
		return m_pCachedPhysicsInfo;
	}
}