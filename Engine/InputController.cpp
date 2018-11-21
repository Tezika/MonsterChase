#include "stdafx.h"
#include "InputController.h"

namespace MonsterChase
{
	InputController::InputController()
	{

	}

	InputController::~InputController()
	{

	}

	void InputController::UpdateGameObject(const Engine::GameObject & i_other)
	{

	}

	void InputController::SetGameObject(Engine::GameObject & i_other)
	{
		this->m_pControlObject = &i_other;
	}
}