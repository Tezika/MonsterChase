#include "stdafx.h"
#include "CollisionPair.h"
#include "Assert.h"

namespace Engine
{
	namespace Physics
	{
		CollisionPair::CollisionPair( float i_collisionTime, const Vector3SSE & i_collisionNormal, PhysicsInfo * i_pPhysicsInfoA, PhysicsInfo * i_pPhysicsInfoB ) :
			m_collisionTime( i_collisionTime ),
			m_collisionNormal( i_collisionNormal )
		{
			assert( i_pPhysicsInfoA );
			assert( i_pPhysicsInfoB );
			m_pCollidables[0] = i_pPhysicsInfoA;
			m_pCollidables[1] = i_pPhysicsInfoB;
		}

		CollisionPair::CollisionPair( const CollisionPair & i_other ) :
			m_collisionTime( i_other.m_collisionTime ),
			m_collisionNormal( i_other.m_collisionNormal )
		{
			m_pCollidables[0] = i_other.m_pCollidables[0];
			m_pCollidables[1] = i_other.m_pCollidables[1];
		}

		void CollisionPair::operator=( const CollisionPair & i_other )
		{
			m_collisionTime = i_other.m_collisionTime;
			m_collisionNormal = i_other.m_collisionNormal;
			m_pCollidables[0] = i_other.m_pCollidables[0];
			m_pCollidables[1] = i_other.m_pCollidables[1];
		}
	}
}