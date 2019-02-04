#pragma once
#include "IController.h"
#include "GameObject.h"
#include "PhysicsInfo.h"

namespace MonsterChase
{
	class InputController : public Engine::IController
	{
	public:
		InputController();
		InputController( Engine::GameObject * i_pGO, float i_drivingForce );

		void UpdateGameObject( float i_dt ) override;

		inline void SetDrivingForce( const float & i_moveSpeed ) { this->m_drivingForce = i_moveSpeed; }
		inline const float & GetDrivingForce() { return this->m_drivingForce; }

		inline void SetControlGameObject( Engine::GameObject & i_other ) override { this->m_pControlObject = &i_other; }
		inline void SetControlGameObject( Engine::GameObject * i_pOther ) override { this->m_pControlObject = i_pOther; }

		inline Engine::GameObject * GetControlGameObject(){ return m_pControlObject; }
		inline Engine::Physics::PhysicsInfo * GetPhysicsInfo();

		~InputController();
	private:
		Engine::GameObject * m_pControlObject;
		Engine::Physics::PhysicsInfo * m_pCachedPhysicsInfo;
		float m_drivingForce;
	};
}
