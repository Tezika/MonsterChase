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

			Node<PhysicsInfo> * ptr_1 = m_pPhysicsInfos->GetHead();
			ptr = m_pPhysicsInfos->GetHead();
			while ( ptr != nullptr )
			{
				while ( ptr_1 != nullptr )
				{
					if ( ptr == ptr_1 )
					{
						ptr_1 = ptr_1->GetNext();
						continue;
					}
					pGoA = ptr->GetData()->GetGameObject();
					assert( pGoA );
					pABB = ptr->GetData()->GetAABB();
					assert( pABB );

					pGoB = ptr_1->GetData()->GetGameObject();
					assert( pGoB );
					pBBB = ptr_1->GetData()->GetAABB();
					assert( pBBB );

					this->CheckCollision( pGoA, pGoB, pABB, pBBB );
					this->CheckCollision( pGoB, pGoA, pBBB, pABB );

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

		bool PhysicsManager::CheckCollision( SmartPtr<GameObject> pGoA, SmartPtr<GameObject> pGoB, AABB * pABB, AABB * pBBB )
		{
			bool bSucceed = false;
			bool bCollided = false;

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


			// Calculate the relative velocity in the world
			Vector3 velARelB = pGoA->GetVelocity() - pGoB->GetVelocity();
			// Translate it into the B's coordinate ( Here we do not need to apply the translation, so we just assign the zero to w. )
			Vector4 velAInB = mtx_WorldToB * Vector4( velARelB, 0 );

			// Check for X axis 

			// Check for Y axis

			return bCollided;
		}
	}
}