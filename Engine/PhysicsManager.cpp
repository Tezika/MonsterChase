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
			// Update the AABB info in wolrd

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

		bool PhysicsManager::CheckCollision( SmartPtr<GameObject> pGoA, SmartPtr<GameObject> pGoB, PhysicsInfo * pPhysicsInfoA, PhysicsInfo * PhysicsInfoB )
		{
			bool bSucceed = false;
			bool bCollided = false;
			// Calculate the necessary matrixes
			Matrix4x4 mtx_AToWorld = pGoA->GetMatrixFromLocalToWorld();
			Matrix4x4 mtx_WorldToA;
			bSucceed = mtx_AToWorld.Invert( mtx_WorldToA );
			assert( bSucceed );

			Matrix4x4 mtx_BToWorld = pGoB->GetMatrixFromLocalToWorld();
			Matrix4x4 mtx_WorldToB;
			bSucceed = mtx_BToWorld.Invert( mtx_WorldToB );
			assert( bSucceed );

			Matrix4x4 mtx_AToB = mtx_WorldToB * mtx_AToWorld;

			// Calculate the relative velocity in the world
			Vector3 velARelB = pGoA->GetVelocity() - pGoB->GetVelocity();
			// Change it into the B's coordinate
			Vector4 velAInB = mtx_WorldToB * Vector4( velARelB, 0.0f );


			return bCollided;
		}
	}
}