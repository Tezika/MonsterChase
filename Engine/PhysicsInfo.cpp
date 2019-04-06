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
		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, SmartPtr<GameObject> i_pGo, AABB * i_pAABB )
		{
			return new PhysicsInfo( i_mass, i_drag, i_pGo, i_pAABB );
		}

		PhysicsInfo::PhysicsInfo( float i_mass, float i_drag, SmartPtr<GameObject> i_pGo, AABB * i_pAABB ) :
			m_dragness( i_drag ),
			m_mass( i_mass ),
			m_pGo( i_pGo ),
			m_pAABB( i_pAABB ),
			m_force( Vector3::Zero )
		{
		}

		PhysicsInfo::~PhysicsInfo()
		{
			if ( m_pAABB != nullptr )
			{
				delete m_pAABB;
			}
		}

		void PhysicsInfo::UpdateAABB()
		{
			// Create the Matrix from local coordinate to world
			Matrix4x4 mtx_translation = Matrix4x4::CreateTranslation( m_pGo->GetPosition() );
			Matrix4x4 mtx_zRotation = Matrix4x4::CreateRotationZ( m_pGo->GetZRot() );
			Matrix4x4 mtx_ObjToWorld = mtx_translation * mtx_zRotation;

			Vector4 aabbCenterInWorld = mtx_ObjToWorld * Vector4( m_pAABB->center.m_x, m_pAABB->center.m_y, 0, 1 );
		}
	}
}
