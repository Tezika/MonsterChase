#include "stdafx.h"
#include "PhysicsManager.h"
#include "PhysicsInfo.h"
#include "TList.h"
#include "Assert.h"
#include "GameObject.h"
#include "Point2D.h"

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
			Point2D<float> cacheAccerlation;
			Point2D<float> cacheVelocity;
			Point2D<float> cacheAverageVelocity;
			Point2D<float> cachePosition;
			GameObject * pCacheGo;
			while ( ptr != nullptr )
			{
				PhysicsInfo * pInfo = ptr->GetData();
				pCacheGo = pInfo->GetGameObject();
				// Caculate the accerlation
				cacheAccerlation = pInfo->GetDrivingForce() / pInfo->GetMass();
				// Use the acceraltion to update the velocity of current gameobject
				cacheVelocity = pCacheGo->GetVelocity();
				cacheVelocity += cacheAccerlation * i_dt;
				// caluate the drag
				float drag = pInfo->GetDragness() * ( cacheVelocity * cacheVelocity );
				// Apply the drag effect to current velocity
				cacheVelocity -= cacheVelocity.Normalize() * drag;

				// Update the velocity for go
				pCacheGo->SetVelocity( cacheVelocity + cacheAccerlation * i_dt );
				// Caluate the average velocity between this frame and last frame
				cacheAverageVelocity = ( cacheVelocity + pCacheGo->GetVelocity() ) / 2;

				// Update the position based on the average velocity
				cachePosition = pCacheGo->GetPosition();
				pCacheGo->SetPosition( cachePosition + cacheAverageVelocity * i_dt );
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
	}
}