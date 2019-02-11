#pragma once
#include "IController.h"
#include "GameObject.h"
#include "SmartPtr.h"

namespace MonsterChase
{
	//Simple AI Controller: Move assigned GameObject towards the player.
	class AIController : public Engine::IController
	{
	public:
		AIController();

		void UpdateGameObject( float i_dt ) override;

		inline void SetControlGameObject( const Engine::SmartPtr<Engine::GameObject> & i_other ) override { this->m_pObject = i_other; }

		inline void SetPlayer( const Engine::SmartPtr<Engine::GameObject> & i_player ) { m_pPlayer = i_player; }

		inline void SetMoveSpeed( const unsigned int i_moveSpeed ) { this->m_moveSpeed = i_moveSpeed; }
		inline const unsigned int GetMoveSpeed() { return this->m_moveSpeed; }

		~AIController();
	private:
		Engine::SmartPtr<Engine::GameObject> m_pPlayer;
		Engine::SmartPtr<Engine::GameObject> m_pObject;
		unsigned int m_moveSpeed;
	};
}
