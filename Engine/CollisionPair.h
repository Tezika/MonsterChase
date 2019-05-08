#pragma once
#include "Vector3SSE.h"

namespace Engine
{
	namespace Physics
	{
		class PhysicsInfo;

		struct CollisionPair
		{
		public:
			float m_collisionTime;
			Vector3SSE  m_collisionNormal;
			PhysicsInfo * m_pCollidables[2];

			CollisionPair(){};
			CollisionPair( float i_collisionTime, const Vector3SSE & i_collisionNormal, PhysicsInfo * i_pPhysicsInfoA, PhysicsInfo * i_pPhysicsInfoB );
			CollisionPair( const CollisionPair & i_other );
			void operator= ( const CollisionPair & i_other );
		};
	}
}