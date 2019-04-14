#include "stdafx.h"
#include "CollisionPair.h"
#include "Assert.h"

namespace Engine
{
	namespace Physics
	{
		CollisionPair::CollisionPair( float i_collisionTime, Vector3 i_collisionNormal, PhysicsInfo * i_pPhysicsInfoA, PhysicsInfo * i_pPhysicsInfoB ) :
			m_collisionTime( i_collisionTime ),
			m_collisionNormal( i_collisionNormal )
		{
			assert( i_pPhysicsInfoA );
			assert( i_pPhysicsInfoB );
			m_pCollidables[0] = i_pPhysicsInfoA;
			m_pCollidables[1] = i_pPhysicsInfoB;
		}

		CollisionPair::CollisionPair( const CollisionPair & i_pOther ) :
			m_collisionTime( i_pOther.m_collisionTime ),
			m_collisionNormal( i_pOther.m_collisionNormal )
		{
			m_pCollidables[0] = i_pOther.m_pCollidables[0];
			m_pCollidables[1] = i_pOther.m_pCollidables[1];
		}
	}
}