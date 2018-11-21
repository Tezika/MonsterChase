#pragma once
#include "PlayerController.h"

namespace MonsterChase
{
	PlayerController::PlayerController()
	{

	}

	PlayerController::~PlayerController()
	{

	}

	void PlayerController::UpdateGameObject(const Engine::GameObject & i_other)
	{
	}

	void PlayerController::SetGameObject(Engine::GameObject & i_other)
	{
		this->m_pPlayer = &i_other;
	}
}