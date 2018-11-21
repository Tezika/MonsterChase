#pragma once
#include "IController.h"

namespace MonsterChase
{
	class InputController : Engine::IController
	{
	public:
		InputController();
		void SetGameObject(Engine::GameObject & i_other) override;
		void UpdateGameObject(const Engine::GameObject & i_other) override;

	protected:
		~InputController();

	private:
		Engine::GameObject * m_pControlObject;
	};
}
