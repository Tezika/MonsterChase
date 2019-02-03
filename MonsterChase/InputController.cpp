#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include <iostream>
#include "game.h"

namespace MonsterChase
{
	InputController::InputController()
	{

	}

	InputController::~InputController()
	{
		m_pControlObject = nullptr;
	}

	void InputController::UpdateGameObject( float i_dt )
	{
	}
}