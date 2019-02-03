#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"

namespace Engine
{
	namespace Physics
	{

		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, GameObject * i_pGo )
		{
			return new PhysicsInfo( i_mass, i_drag, i_pGo );
		}

		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo ) :
			m_dragness( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo ),
			m_force( Point2D<float>( 0, 0 ) )
		{
		}

		PhysicsInfo::~PhysicsInfo()
		{
			m_pGo = nullptr;
		}
	}
}
