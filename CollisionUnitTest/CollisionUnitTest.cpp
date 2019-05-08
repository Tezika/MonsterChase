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

int main()
{
	srand( time_t( NULL ) );
	std::cout << "Hello World!\n";
}

//void CollisionPoolCheck()
//{
//	using namespace Engine;
//
//	const float AreaExtent = 10.0f;
//	Vector3 PositionMin( -AreaExtent, -AreaExtent, -AreaExtent );
//	Vector3 PositionMax( AreaExtent, AreaExtent, AreaExtent );
//
//	Vector3 VelocityMin( -1.0f, -1.0f, -1.0f );
//	Vector3 VelocityMax( 1.0f, 1.0f, 1.0f );
//
//	const size_t numObjects = 100;
//
//	for ( size_t i = 0; i < numObjects; i++ )
//	{
//		GameObject	*pObj = new GameObject;
//
//		pObj->m_Position = GenerateRandomVector( PositionMin, PositionMax );
//		pObj->m_Velocity = GenerateRandomVector( VelocityMin, VelocityMax );
//
//		switch ( rand() & 0x03 )
//		{
//		case 01:
//			pObj->m_Orientation = Matrix3::CreateXRotationCV( RandInRange( 0.0f, 90.0f ) );
//			break;
//		case 02:
//			pObj->m_Orientation = Matrix3::CreateYRotationCV( RandInRange( 0.0f, 90.0f ) );
//			break;
//		case 03:
//			pObj->m_Orientation = Matrix3::CreateZRotationCV( RandInRange( 0.0f, 90.0f ) );
//			break;
//		default:
//			pObj->m_Orientation = Matrix3::Identity;
//			break;
//		}
//
//		pObj->m_BB.m_Center = Vector3( 0.0f, 0.0f, 0.0f );
//		pObj->m_BB.m_Extents = Vector3( 0.5f, 0.5f, 0.5f );
//
//		m_CollisionObjects.push_back( pObj );
//	}
//
//	while ( 1 )
//		CollisionPair Pair = FindCollision( RandInRange( 0.1f, 1.0f ) );
//}
//
//Engine::Physics::CollisionPair FindCollision( float i_dt )
//{
//	Engine::Physics::CollisionPair CurrentCollision = { { 0, 0 }, 0.0f };
//
//	const size_t count = m_CollisionObjects.size();
//
//	for ( size_t i = 0; i < ( count - 1 ); i++ )
//	{
//		for ( size_t j = i + 1; j < count; j++ )
//		{
//			assert( m_CollisionObjects[i] );
//			assert( m_CollisionObjects[j] );
//
//			float tCollision = 0.0f;
//
//			if ( CheckCollision( *m_CollisionObjects[i], *m_CollisionObjects[j], i_dt, tCollision ) )
//			{
//				if ( CurrentCollision.m_pObjects[0] )
//				{
//					if ( tCollision < CurrentCollision.m_CollisionTime )
//					{
//						CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
//						CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
//						CurrentCollision.m_CollisionTime = tCollision;
//					}
//				}
//				else
//				{
//					CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
//					CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
//					CurrentCollision.m_CollisionTime = tCollision;
//				}
//			}
//		}
//	}
//	return CurrentCollision;
//}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
