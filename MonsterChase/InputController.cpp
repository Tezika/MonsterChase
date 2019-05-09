#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include <iostream>
#include "game.h"
#include "GLib.h"
#include "PhysicsManager.h"
#include "Vector3.h"
#include "ConsolePrint.h"

namespace FinalProject
{
	void InputCallback( unsigned int i_VKeyID, bool bWentDown )
	{
		using namespace Engine;
		// Access the current player's controller.
		InputController * pCurrentController = static_cast<InputController *>( Game::GetInstance().GetPlayer1()->GetController() );
		Physics::PhysicsInfo * pCachedPhysicsInfo = pCurrentController->GetPhysicsInfo();
		static Vector3 cachedDrivingForce = Vector3::Zero;
		if ( bWentDown )
		{
			// Maybe need to encapsulate a little bit better.
			// If I want to make it support the arrow keys, I need to modify the input.cpp from GLib.
			switch ( i_VKeyID )
			{
				// For W
			case 0x57:
				cachedDrivingForce.x = 0;
				cachedDrivingForce.y = pCurrentController->GetDrivingForce();
				DEBUG_PRINT_GAMEPLAY( "Start applying the force with direction of up" );
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
		pCachedPhysicsInfo->SetDrivingForce( Vector3SSE{ cachedDrivingForce.x, cachedDrivingForce.y, cachedDrivingForce.z } );
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

	Engine::Physics::PhysicsInfo * InputController::GetPhysicsInfo()
	{
		if ( m_pCachedPhysicsInfo == nullptr )
		{
			m_pCachedPhysicsInfo = Engine::Physics::PhysicsManager::GetInstance().GetInfoByGameObject( m_pControlObject );
		}
		return m_pCachedPhysicsInfo;
	}
}