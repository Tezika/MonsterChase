#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include <iostream>
#include "game.h"
#include "GLib.h"

namespace MonsterChase
{
	void InputCallback( unsigned int i_VKeyID, bool bWentDown )
	{
		DEBUGE_PRINT_GAMEPLAY( "Detected the user's input change!" );
	}

	InputController::InputController()
	{
		GLib::SetKeyStateChangeCallback( InputCallback );

	}

	InputController::~InputController()
	{
		m_pControlObject = nullptr;
	}

	void InputController::UpdateGameObject( float i_dt )
	{
	}


}