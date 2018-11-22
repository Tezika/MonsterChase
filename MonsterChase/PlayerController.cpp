#pragma once
#include "PlayerController.h"
#include "game.h"

namespace MonsterChase
{
	PlayerController::PlayerController()
	{

	}

	PlayerController::~PlayerController()
	{

	}

	void PlayerController::UpdateGameObject()
	{
	}

	void PlayerController::SetGameObject(Engine::GameObject & i_other)
	{
		this->m_pPlayer = &i_other;
	}
}