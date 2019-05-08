// CollisionUnitTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include "Vector3.h"
#include "Vector3SSE.h"
#include "Vector4.h"
#include "Vector4SSE.h"
#include "GameObject.h"
#include "CollisionPair.h"
#include "Timer.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "SmartPtr.h"
#include "AABB.h"
#include "PhysicsInfo.h"
#include "PhysicsManager.h"
#include "Assert.h"
#include "Engine-init.h"
#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

float RandomInRange( float min, float max )
{
	// Prevent the situation while the max equals the min.
	if ( max - min == 0 )
	{
		return 0;
	}
	return min + static_cast<float>( rand() / ( static_cast<float>( RAND_MAX / ( max - min ) ) ) );
}

Engine::Vector3SSE GenerateRandomVectorSSE( const Engine::Vector3SSE & i_min, const Engine::Vector3SSE & i_max )
{
	float x = RandomInRange( i_min.x(), i_max.x() );
	float y = RandomInRange( i_min.y(), i_max.y() );
	float z = RandomInRange( i_min.z(), i_max.z() );
	return Engine::Vector3SSE( x, y, z );
}

std::vector<Engine::Physics::PhysicsInfo> m_physicsInfos;


Engine::Physics::CollisionPair FindCollision( float i_dt )
{
	using namespace Engine;
	Engine::Physics::CollisionPair CurrentCollision;

	const size_t count = m_physicsInfos.size();

	for ( size_t i = 0; i < ( count - 1 ); i++ )
	{
		for ( size_t j = i + 1; j < count; j++ )
		{
			assert( &m_physicsInfos[i] );
			assert( &m_physicsInfos[j] );

			float tCollision = 0.0f;
			bool collided = false;

#ifdef SSE_COLLISIONCHECK
			Vector3SSE collisionNormal;
			collided = Physics::PhysicsManager::GetInstance().IsCollisionSSE( &m_physicsInfos[i], &m_physicsInfos[j], i_dt, tCollision, collisionNormal );
#else
			Vector3 collisionNormal;
			collided = Physics::PhysicsManager::GetInstance().IsCollision( &m_physicsInfos[i], &m_physicsInfos[j], i_dt, tCollision, collisionNormal );
#endif

			if ( collided )
			{
				if ( CurrentCollision.m_pCollidables[0] )
				{
					if ( tCollision < CurrentCollision.m_collisionTime )
					{
						CurrentCollision.m_pCollidables[0] = &m_physicsInfos[i];
						CurrentCollision.m_pCollidables[1] = &m_physicsInfos[j];
						CurrentCollision.m_collisionTime = tCollision;
#ifdef SSE_COLLISIONCHECK
						CurrentCollision.m_collisionNormal = collisionNormal;
#else
						CurrentCollision.m_collisionNormal = Vector3SSE( collisionNormal.x, collisionNormal.y, collisionNormal.z );
#endif // SSE_COLLISIONCHECK
					}
				}
				else
				{
					CurrentCollision.m_pCollidables[0] = &m_physicsInfos[i];
					CurrentCollision.m_pCollidables[1] = &m_physicsInfos[j];
					CurrentCollision.m_collisionTime = tCollision;
#ifdef SSE_COLLISIONCHECK
					CurrentCollision.m_collisionNormal = collisionNormal;
#else
					CurrentCollision.m_collisionNormal = Vector3SSE( collisionNormal.x, collisionNormal.y, collisionNormal.z );
#endif // SSE_COLLISIONCHECK
				}
			}
		}
	}
	return CurrentCollision;
}

void CollisionPoolCheck()
{
	using namespace Engine;

	const float AreaExtent = 30.0f;
	const float VeclocityExtent = 300.0f;

	Vector3SSE PositionMin( -AreaExtent, -AreaExtent, 0 );
	Vector3SSE PositionMax( AreaExtent, AreaExtent, 0 );

	Vector3SSE VelocityMin( -VeclocityExtent, -VeclocityExtent, 0 );
	Vector3SSE VelocityMax( VeclocityExtent, VeclocityExtent, 0 );

	const size_t numObjects = 100;

	for ( size_t i = 0; i < numObjects; i++ )
	{
		Vector3SSE initialPosition = GenerateRandomVectorSSE( PositionMin, PositionMax );
		Vector3SSE initialVelocity = GenerateRandomVectorSSE( VelocityMin, VelocityMax );

		SmartPtr<GameObject> pNewGo = GameObject::Create( "dummyObject", initialPosition );
		pNewGo->SetVelocity( initialVelocity );
		pNewGo->SetZRot( RandomInRange( 0, 180 ) );
		// Create and assign the AABB to the physicsinfo
		AABB * aabb = AABB::Create( Point2D<float>{ 16, 16 }, Point2D<float>{16, 16} );
		// Create the player's physics info
		Physics::PhysicsInfo * pPhysicsInfo = Physics::PhysicsInfo::Create( 1.0, 0.0f, true, pNewGo, aabb );
		pPhysicsInfo->SetDrivingForce( Vector3SSE{ 0, 0, 0 } );
		m_physicsInfos.push_back( *pPhysicsInfo );
	}

	while ( 1 )
		Physics::CollisionPair pPair = FindCollision( RandomInRange( 0.1f, 1.0f ) );
}

int main()
{
	srand( time_t( NULL ) );
	CollisionPoolCheck();
	std::cout << "Hello World!\n";
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
