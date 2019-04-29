#include "stdafx.h"
#include "PhysicsInfo.h"
#include "GameObject.h"
#include "AABB.h"
#include "Matrix4x4.h"
#include "ConsolePrint.h"
#include "Vector3.h"
#include "Vector4.h"
#include "RenderManager.h"
#include "MessageSystem.h"
#include "Delegate.h"
#include "HashString.h"

namespace Engine
{
	namespace Physics
	{
		PhysicsInfo * PhysicsInfo::Create( float i_mass, float i_drag, bool i_bCollidable, SmartPtr<GameObject> i_pGo, AABB * i_pAABB )
		{
			PhysicsInfo * newPhysicsInfo = new PhysicsInfo( i_mass, i_drag, i_bCollidable, i_pGo, i_pAABB );
			Messaging::Delegate<> testCollisionDelegate = Messaging::Delegate<>::Create<PhysicsInfo, &PhysicsInfo::OnCollision>( newPhysicsInfo );
			Messaging::MessageSystem::GetInstance().RegisterMessageDelegate( "TestOnCollision", testCollisionDelegate );
			return newPhysicsInfo;
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

		PhysicsInfo::PhysicsInfo( const PhysicsInfo & i_other ) :
			m_dragness( i_other.m_dragness ),
			m_mass( i_other.m_mass ),
			m_pGo( i_other.m_pGo ),
			m_force( Vector3::Zero ),
			m_bIsCollision( i_other.m_bIsCollision ),
			m_bCollidable( i_other.m_bCollidable )
		{
			m_pAABB = AABB::Create( i_other.m_pAABB->center, i_other.m_pAABB->extends );
		}

		void PhysicsInfo::operator=( const PhysicsInfo & i_other )
		{
			m_dragness = i_other.m_dragness;
			m_mass = i_other.m_mass;
			m_pGo = i_other.m_pGo;
			m_force = Vector3::Zero;
			m_bIsCollision = i_other.m_bIsCollision;
			m_bCollidable = i_other.m_bCollidable;
			m_pAABB = AABB::Create( i_other.m_pAABB->center, i_other.m_pAABB->extends );
		}

		void PhysicsInfo::OnCollision()
		{
			DEBUG_PRINT_GAMEPLAY( "The %s is on collision right now, this call from the message system.", this->m_pGo->GetName().c_str() );
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
