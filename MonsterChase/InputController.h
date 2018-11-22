#pragma once
#pragma once
#include "IController.h"
#include "GameObject.h"

namespace MonsterChase
{
	class InputController : Engine::IController
	{
	public:
		InputController();
		void SetGameObject(Engine::GameObject & i_other) override;
		void UpdateGameObject() override;

		inline void SetMoveSpeed(const int i_moveSpeed) { this->m_moveSpeed = i_moveSpeed; }
		inline const unsigned int GetMoveSpeed() { return this->m_moveSpeed; }

	protected:
		~InputController();

	private:
		Engine::GameObject * m_pControlObject;
		unsigned int m_moveSpeed;
	};
}
