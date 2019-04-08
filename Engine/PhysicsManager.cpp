#include "stdafx.h"
#include "PhysicsManager.h"
#include "PhysicsInfo.h"
#include "TList.h"
#include "Assert.h"
#include "GameObject.h"
#include "Point2D.h"
#include "SmartPtr.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "AABB.h"
#include <algorithm>
#include <limits>

namespace Engine
{
	namespace Physics
	{
		bool PhysicsManager::Initialize()
		{
			m_pPhysicsInfos = new TList<PhysicsInfo>();
			assert( m_pPhysicsInfos );
			DEBUG_PRINT_ENGINE( "The physics system initialized succuessfully!" );
			return true;
		}

		void PhysicsManager::Simulate( float i_dt )
		{
			// Iterate every physics object in the list
			Node<PhysicsInfo> * ptr = m_pPhysicsInfos->GetHead();
			Vector3 cachedAcceleration;
			Vector3 cachedVelocity;
			Vector3 cachedAverageVelocity;
			Vector3 cachedPosition;
			SmartPtr<GameObject> pCachedGo;
			// Simulate the position
			while ( ptr != nullptr )
			{
				PhysicsInfo * pInfo = ptr->GetData();
				pCachedGo = pInfo->GetGameObject();
				Vector3 drivingForce = pInfo->GetDrivingForce();
				assert( pCachedGo != nullptr );
				// Caculate the accerlation
				cachedAcceleration = drivingForce / pInfo->GetMass();
				// Use the acceraltion to update the velocity of current gameobject
				cachedVelocity = pCachedGo->GetVelocity();
				cachedVelocity += cachedAcceleration * i_dt;
				// caluate the drag
				float drag = pInfo->GetDragness() * ( cachedVelocity.Dot( cachedVelocity ) );
				// Apply the drag effect to current velocity
				cachedVelocity -= cachedVelocity.Normalize() * drag;
				// Update the velocity for go
				pCachedGo->SetVelocity( cachedVelocity + cachedAcceleration * i_dt );
				// Caluate the average velocity between this frame and last frame
				cachedAverageVelocity = ( cachedVelocity + pCachedGo->GetVelocity() ) / 2;
				// Update the position based on the average velocity
				cachedPosition = pCachedGo->GetPosition();
				pCachedGo->SetPosition( cachedPosition + cachedAverageVelocity * i_dt );
				ptr = ptr->GetNext();
			}

			// Check the collision between two objects
			SmartPtr<GameObject> pGoA;
			SmartPtr<GameObject> pGoB;
			AABB * pABB = nullptr;
			AABB * pBBB = nullptr;

			PhysicsInfo * pPhysicsA = nullptr;
			PhysicsInfo * pPhysicsB = nullptr;

			Node<PhysicsInfo> * ptr_1 = m_pPhysicsInfos->GetHead();
			ptr = m_pPhysicsInfos->GetHead();

			float tCloseLatest;
			float tOpenEarilest;
			float bCollided = true;

			while ( ptr != nullptr )
			{
				pPhysicsA = ptr->GetData();

				while ( ptr_1 != nullptr )
				{
					if ( ptr == ptr_1 )
					{
						ptr_1 = ptr_1->GetNext();
						continue;
					}
					// Initialize the min and max value for time;
					tCloseLatest = std::numeric_limits<float>::min();
					tOpenEarilest = std::numeric_limits<float>::max();

					bCollided = true;

					pPhysicsB = ptr_1->GetData();

					pGoA = pPhysicsA->GetGameObject();
					assert( pGoA );
					pABB = pPhysicsA->GetAABB();
					assert( pABB );

					pGoB = pPhysicsB->GetGameObject();
					assert( pGoB );
					pBBB = pPhysicsB->GetAABB();
					assert( pBBB );

					bCollided = this->CheckCollision( pGoA, pGoB, pABB, pBBB, i_dt, tCloseLatest, tOpenEarilest );
					if ( !bCollided )
					{
						pPhysicsA->SetInCollision( false );
						pPhysicsB->SetInCollision( false );
						ptr_1 = ptr_1->GetNext();
						continue;
					}

					bCollided = true;
					bCollided = this->CheckCollision( pGoB, pGoA, pBBB, pABB, i_dt, tCloseLatest, tOpenEarilest );
					if ( !bCollided )
					{
						pPhysicsA->SetInCollision( false );
						pPhysicsB->SetInCollision( false );
						ptr_1 = ptr_1->GetNext();
						continue;
					}

					if ( tCloseLatest < tOpenEarilest )
					{
						pPhysicsA->SetInCollision( true );
						pPhysicsB->SetInCollision( true );
					}
					else
					{
						pPhysicsA->SetInCollision( false );
						pPhysicsB->SetInCollision( false );
					}

					ptr_1 = ptr_1->GetNext();
				}
				ptr = ptr->GetNext();
			}

		}

		bool PhysicsManager::AddPhysicsObject( PhysicsInfo * i_pInfo )
		{
			assert( i_pInfo );
			return m_pPhysicsInfos->InsertToTail( i_pInfo );
		}

		bool PhysicsManager::RemovePhysicsObject( GameObject * i_pGo )
		{
			assert( i_pGo );
			Node<PhysicsInfo> * ptr = m_pPhysicsInfos->GetHead();
			PhysicsInfo * removePhysicsInfo = nullptr;
			while ( ptr != nullptr )
			{
				removePhysicsInfo = ptr->GetData();
				if ( removePhysicsInfo->GetGameObject() == i_pGo )
				{
					assert( removePhysicsInfo );
					ptr = m_pPhysicsInfos->Remove( ptr );
					delete removePhysicsInfo;
				}
				else
				{
					ptr = ptr->GetNext();
				}
			}
			return true;
		}

		PhysicsInfo * PhysicsManager::GetInfoByGameObject( SmartPtr<GameObject> i_pGO )
		{
			assert( i_pGO );
			Node<PhysicsInfo> * ptr = m_pPhysicsInfos->GetHead();
			PhysicsInfo * pCurrentInfo = nullptr;
			while ( ptr != nullptr )
			{
				pCurrentInfo = ptr->GetData();
				if ( pCurrentInfo->GetGameObject() == i_pGO )
				{
					return pCurrentInfo;
				}
				ptr = ptr->GetNext();
			}
			return nullptr;
		}

		bool PhysicsManager::Destroy()
		{
			// Clean the physics objects
			Node<PhysicsInfo> * ptr = m_pPhysicsInfos->GetHead();
			PhysicsInfo * removePhysicsInfo = nullptr;
			while ( ptr != nullptr )
			{
				removePhysicsInfo = ptr->GetData();
				assert( removePhysicsInfo );
				ptr = m_pPhysicsInfos->Remove( ptr );
				delete removePhysicsInfo;
			}
			// Delete the physicsInfo's manager
			delete m_pPhysicsInfos;
			m_pPhysicsInfos = nullptr;

			DEBUG_PRINT_ENGINE( "The physics system destoried succuessfully!" );
			return true;
		}

		bool PhysicsManager::CheckCollision(
			SmartPtr<GameObject> pGoA,
			SmartPtr<GameObject> pGoB,
			AABB * pABB, AABB * pBBB,
			float tFrameEnd,
			float & tCloseLatest,
			float & tOpenEarilest
		)
		{
			// Calculate the necessary matrixes
			Matrix4x4 mtx_AToWorld = pGoA->GetMatrixFromLocalToWorld();
			Matrix4x4 mtx_WorldToA = pGoA->GetMatrixFromWorldToLocal();

			Matrix4x4 mtx_BToWorld = pGoB->GetMatrixFromLocalToWorld();
			Matrix4x4 mtx_WorldToB = pGoB->GetMatrixFromWorldToLocal();

			// Calculate the transform matrix from A to B.
			Matrix4x4 mtx_AToB = mtx_WorldToB * mtx_AToWorld;

			// Translate the bounding box's center from coordinate A to B
			Vector4 ABBCenterInB = mtx_AToB * Vector4( pABB->center.m_x, pABB->center.m_y, 0, 1.0f );

			// Translate it's extends from coordinate A to B
			Vector4 AExtendsXInB = mtx_AToB * Vector4( pABB->extends.m_x, 0.0f, 0.0f, 0.0f );
			Vector4 AExtendsYInB = mtx_AToB * Vector4( 0.0f, pABB->extends.m_y, 0.0f, 0.0f );

			// Calculate the relative velocity in the world
			Vector3 velARelB = pGoA->GetVelocity() - pGoB->GetVelocity();
			// Translate it into the B's coordinate ( Here we do not need to apply the translation, so we just assign the zero to w. )
			Vector4 velAInB = mtx_WorldToB * Vector4( velARelB, 0 );

			// Check for X axis
			bool bCollided = true;
			bCollided = this->CheckAxisCollision( AExtendsXInB.x, AExtendsYInB.x,
				pBBB->extends.m_x, pBBB->center.m_x,
				ABBCenterInB.x,
				velAInB.x,
				tFrameEnd,
				tOpenEarilest,
				tCloseLatest
			);
			if ( !bCollided )
			{
				return false;
			}

			// Check for y axis
			bCollided = true;
			bCollided = this->CheckAxisCollision( AExtendsXInB.y, AExtendsYInB.y,
				pBBB->extends.m_y, pBBB->center.m_y,
				ABBCenterInB.y,
				velAInB.y,
				tFrameEnd,
				tOpenEarilest,
				tCloseLatest
			);
			if ( !bCollided )
			{
				return false;
			}

			return true;
		}

		bool PhysicsManager::CheckAxisCollision(
			float aExtendsXinAxis,
			float aExtendsYInAxis,
			float bBBExtendsInAxis,
			float bBBCenterInAxis,
			float aBBcenterInAxis,
			float velAInBInAxis,
			float tFrameEnd,
			float & tOpenEarilest,
			float & tCloseLatest
		)
		{
			// Check for X axis
			float AProjectOntoB = fabs( aExtendsXinAxis ) + fabs( aExtendsYInAxis );
			float bExtends = bBBExtendsInAxis + AProjectOntoB;
			float bLeft = bBBCenterInAxis - bExtends;
			float bRight = bBBCenterInAxis + bExtends;

			float dClose = bLeft - aBBcenterInAxis;
			float dOpen = bRight - aBBcenterInAxis;

			float tOpen = 0;
			float tClose = 0;

			// When the realtive velocity projection is zero
			if ( velAInBInAxis == 0.0f )
			{
				// If A's bb center outside the Bleft ~ bRight, there is no collision. 
				if ( aBBcenterInAxis < bLeft || aBBcenterInAxis > bRight )
				{
					return false;
				}
			}
			else
			{
				tOpen = dOpen / velAInBInAxis;
				tClose = dClose / velAInBInAxis;
				// A move to B in the -x direction, and we just swap two value
				if ( tOpen < tClose )
				{
					std::swap( tOpen, tClose );
				}
				// Check the edge: If the close happens in the time point after this frame, there should be no collision
				if ( tClose > tFrameEnd )
				{
					return false;
				}
				// Check the edge: If the open's time less than zero, which means the gap should always be in the right, there is no collision too.
				if ( tOpen < 0 )
				{
					return false;
				}
				// When passing the edge check, update the earliest open and latest close time
				tOpenEarilest = tOpen < tOpenEarilest ? tOpen : tOpenEarilest;
				tCloseLatest = tClose > tCloseLatest ? tClose : tCloseLatest;
			}
			return true;
		}
	}
}