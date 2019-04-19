#pragma once
#include "Vector3.h"

namespace Engine
{
	namespace Physics
	{
		class PhysicsInfo;

		struct CollisionPair
		{
		public:
			float m_collisionTime;
			Vector3  m_collisionNormal;
			PhysicsInfo * m_pCollidables[2];

			CollisionPair(){};
			CollisionPair( float i_collisionTime, const Vector3 & i_collisionNormal, PhysicsInfo * i_pPhysicsInfoA, PhysicsInfo * i_pPhysicsInfoB );
			CollisionPair( const CollisionPair & i_pOther );
		};
	}
}