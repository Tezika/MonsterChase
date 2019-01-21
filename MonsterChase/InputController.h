#pragma once
#include "IController.h"
#include "GameObject.h"

namespace MonsterChase
{
	class InputController : public Engine::IController
	{
	public:
		InputController();

		void UpdateGameObject() override;

		inline void SetMoveSpeed( const int i_moveSpeed ) { this->m_moveSpeed = i_moveSpeed; }
		inline const unsigned int GetMoveSpeed() { return this->m_moveSpeed; }

		inline void SetGameObject( Engine::GameObject & i_other ) override { this->m_pControlObject = &i_other; }
		inline void SetGameObject( Engine::GameObject * i_pOther ) override { this->m_pControlObject = i_pOther; }

		~InputController();
	private:
		Engine::GameObject * m_pControlObject;
		unsigned int m_moveSpeed;
	};
}
