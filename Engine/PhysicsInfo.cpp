#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"

namespace Engine
{
	namespace Physics
	{

		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, GameObject * i_pGo, Point2D<float> & i_oForce )
		{
			return new PhysicsInfo( i_mass, i_drag, i_pGo, i_oForce );
		}

		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo, Point2D<float> & i_oForce ) :
			m_dragness( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo ),
			m_force( i_oForce )
		{
		}

		PhysicsInfo::~PhysicsInfo()
		{
			m_pGo = nullptr;
		}
	}
}
