#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"
#include "AABB.h"

namespace Engine
{
	namespace Physics
	{

		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, SmartPtr<GameObject> i_pGo, AABB * i_pAABB )
		{
			return new PhysicsInfo( i_mass, i_drag, i_pGo, i_pAABB );
		}

		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, SmartPtr<GameObject> i_pGo, AABB * i_pAABB ) :
			m_dragness( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo ),
			m_pAABB( i_pAABB ),
			m_force( Point2D<float>( 0, 0 ) )
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
