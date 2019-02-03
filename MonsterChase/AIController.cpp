#pragma once
#include "AIController.h"
#include "game.h"

namespace MonsterChase
{
	AIController::AIController()
	{
	}

	AIController::~AIController()
	{
		m_pObject = nullptr;
		m_pPlayer = nullptr;
	}

	void AIController::UpdateGameObject( float i_dt )
	{
	}
}