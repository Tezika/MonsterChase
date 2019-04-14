#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"
#include "AABB.h"
#include "Matrix4x4.h"
#include "ConsolePrint.h"
#include "Vector3.h"
#include "Vector4.h"
#include "RenderManager.h"

namespace Engine
{
	namespace Physics
	{
		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, bool i_bCollidable, SmartPtr<GameObject> i_pGo, AABB * i_pAABB )
		{
			return new PhysicsInfo( i_mass, i_drag, i_bCollidable, i_pGo, i_pAABB );
		}

		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, bool i_bCollidable, SmartPtr<GameObject> i_pGo, AABB * i_pAABB ) :
			m_dragness( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo ),
			m_pAABB( i_pAABB ),
			m_force( Vector3::Zero ),
			m_bIsCollision( false ),
			m_bCollidable( i_bCollidable )
		{
		}

		PhysicsInfo::~PhysicsInfo()
		{
			if ( m_pAABB != nullptr )
			{
				delete m_pAABB;
			}
		}
	}
}
