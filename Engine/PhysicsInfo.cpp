#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"

namespace Engine
{
	namespace Physics
	{
		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo ) :
			m_drag( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo )
		{
		}

		PhysicsInfo::~PhysicsInfo()
		{
			m_pGo = nullptr;
		}
	}
}
