#pragma once
#include "IController.h"

namespace MonsterChase
{
	class InputController : Engine::IController
	{
	public:
		InputController();
		void UpdateGameObject(const Engine::GameObject & i_other) override;
	protected:
		~InputController();
	};
}

