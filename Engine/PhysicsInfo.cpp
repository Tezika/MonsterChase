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

		void PhysicsInfo::UpdateAABB()
		{
			// Update the AABB center position
			Matrix4x4 mtx_translation = Matrix4x4::CreateTranslation( Vector3( m_pGo->GetPosition().m_x, m_pGo->GetPosition().m_y, 0 ) );
			Matrix4x4 mtx_zRotation = Matrix4x4::CreateRotationZ( m_pGo->GetZRot() );
			Matrix4x4 mtx_ObjToWorld = mtx_translation * mtx_zRotation;

			Vector4 aabbCenterInWorld = mtx_ObjToWorld * Vector4( m_pAABB->center.m_x, m_pAABB->center.m_y, 0, 1 );
			// Draw a debug dot to indicate the position of the AABB center on the canvas.
			Render::RenderManager::GetInstance().DrawDebugDot( aabbCenterInWorld.x, aabbCenterInWorld.y );
		}
	}
}
