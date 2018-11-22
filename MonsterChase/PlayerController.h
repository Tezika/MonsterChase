#pragma once
#include "IController.h"
#include "GameObject.h"

namespace MonsterChase
{
	//Move a GameObject towards the player
	class PlayerController : Engine::IController
	{
	public:
		PlayerController();
		void SetGameObject(Engine::GameObject & i_other) override;
		void UpdateGameObject() override;

		inline void SetPlayer(Engine::GameObject & i_player) { m_pPlayer = &i_player; }

		inline void SetMoveSpeed(const int i_moveSpeed) { this->m_moveSpeed = i_moveSpeed; }
		inline const unsigned int GetMoveSpeed() { return this->m_moveSpeed; }

	protected:
		~PlayerController();

	private:
		Engine::GameObject * m_pPlayer;
		Engine::GameObject * m_pObject;
		unsigned int m_moveSpeed;
	};
}
