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
			DEBUG_PRINT( "The physics system initialized succuessfully!" );
			return true;
		}

		void PhysicsManager::Update( float i_dt )
		{
			// Iterate every physics objects in the list
			Node<PhysicsInfo> * ptr = m_pPhysicsInfos->GetHead();
			while ( ptr != nullptr )
			{
				PhysicsInfo * pInfo = ptr->GetData();
				// Caculate the accerlate
				Point2D<float> acceleration = pInfo->GetDirOfForce() / pInfo->GetMass();
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

			DEBUG_PRINT( "The physics system destoried succuessfully!" );
			return true;
		}
	}
}