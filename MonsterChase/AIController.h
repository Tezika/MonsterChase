#pragma once
#include "IController.h"
#include "GameObject.h"

namespace MonsterChase
{
	//Simple AI Controller: Move assigned GameObject towards the player.
	class AIController : public Engine::IController
	{
	public:
		AIController();

		void UpdateGameObject() override;

		inline void SetGameObject( Engine::GameObject & i_other ) override { this->m_pObject = &i_other; }
		inline void SetGameObject( Engine::GameObject * i_pOther ) override { this->m_pObject = i_pOther; }

		inline void SetPlayer( Engine::GameObject & i_player ) { m_pPlayer = &i_player; }
		inline void SetPlayer( Engine::GameObject * i_pPlayer ){ m_pPlayer = i_pPlayer; }

		inline void SetMoveSpeed( const unsigned int i_moveSpeed ) { this->m_moveSpeed = i_moveSpeed; }
		inline const unsigned int GetMoveSpeed() { return this->m_moveSpeed; }

		~AIController();
	private:
		Engine::GameObject * m_pPlayer;
		Engine::GameObject * m_pObject;
		unsigned int m_moveSpeed;
	};
}
