#pragma once
#include "IController.h"
#include "GameObject.h"
#include "PhysicsInfo.h"
#include "SmartPtr.h"

namespace MonsterChase
{
	class InputController : public Engine::IController
	{
	public:
		InputController();
		InputController( Engine::SmartPtr<Engine::GameObject> i_pGo, float i_drivingForce );

		void UpdateGameObject( float i_dt ) override;

		inline void SetDrivingForce( const float & i_moveSpeed ) { this->m_drivingForce = i_moveSpeed; }
		inline const float & GetDrivingForce() { return this->m_drivingForce; }

		inline void SetControlGameObject( const Engine::SmartPtr<Engine::GameObject> & i_other ) override { this->m_pControlObject = i_other; }

		inline Engine::SmartPtr<Engine::GameObject> GetControlGameObject(){ return m_pControlObject; }
		inline Engine::Physics::PhysicsInfo * GetPhysicsInfo();

		~InputController();
	private:
		Engine::SmartPtr<Engine::GameObject> m_pControlObject;
		Engine::Physics::PhysicsInfo * m_pCachedPhysicsInfo;
		float m_drivingForce;
	};
}
