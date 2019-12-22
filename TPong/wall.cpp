#include "stdafx.h"
#include "wall.h"
#include "MessageSystem.h"
#include "CollisionPair.h"
#include "PhysicsInfo.h"
#include "ConsolePrint.h"

namespace TPong
{
	Wall::Wall() :
		Entity::Entity(), m_bDead( false )
	{
	}

	Wall::Wall( const Engine::HashedString& i_name, const Engine::Vector3SSE& i_position ) :
		Entity::Entity( i_name, i_position ), m_bDead( false )
	{
	}

	void Wall::SetDead()
	{
		using namespace Engine;
		m_bDead = true;
		// Register the delegate for the collision event
		this->m_dOnCollision = Messaging::Delegate<void*>::Create<Wall, & Wall::OnCollision>( this );
		Messaging::MessageSystem::GetInstance().RegisterMessageDelegate( "OnCollision", this->m_dOnCollision );
	}

	void Wall::OnCollision( void* i_pCollisionInfo )
	{
		using namespace Engine;
		using namespace Engine::Physics;
		CollisionPair* pCollisionPair = reinterpret_cast<CollisionPair*>(i_pCollisionInfo);
		assert( pCollisionPair );
		SmartPtr<GameObject> pGO1 = pCollisionPair->m_pCollidables[0]->GetGameObject();
		SmartPtr<GameObject> pGO2 = pCollisionPair->m_pCollidables[1]->GetGameObject();
		if (pGO1 == this || pGO2 == this)
		{
			Messaging::MessageSystem::GetInstance().SendMessageW( "OnBallCollideDeadWall", this );
		}
	}

	Wall::~Wall()
	{
		using namespace Engine;
		if (m_bDead)
		{
			Messaging::MessageSystem::GetInstance().DeregisterMessageDelegate( "OnCollision", this->m_dOnCollision );
		}
	}
}