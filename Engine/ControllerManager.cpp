#include "stdafx.h"
#include "ControllerManager.h"
#include "IController.h"
#include "Assert.h"
#include "TList.h"

namespace Engine
{
	namespace Controller
	{

		bool ControllerManager::AddContrller( IController * i_pController )
		{
			assert( i_pController );
			return m_pControllers->InsertToTail( i_pController );
		}

		bool ControllerManager::RemovePhysicsObject( IController * i_pController )
		{
			assert( i_pController );
			Node<IController> * ptr = m_pControllers->GetHead();
			IController * removeController = nullptr;
			while ( ptr != nullptr )
			{
				removeController = ptr->GetData();
				if ( removeController == i_pController )
				{
					assert( removeController );
					ptr = m_pControllers->Remove( ptr );
					delete removeController;
				}
				else
				{
					ptr = ptr->GetNext();
				}
			}
			return true;
		}

		bool ControllerManager::Initialize()
		{
			m_pControllers = new TList<IController>();
			assert( m_pControllers );
			DEBUG_PRINT( "The controller manager initialized succuessfully!" );
			return true;
		}

		void ControllerManager::Update( float i_dt )
		{
			Node<IController> * ptr = m_pControllers->GetHead();
			while ( ptr != nullptr )
			{
				ptr->GetData()->UpdateGameObject( i_dt );
				ptr = ptr->GetNext();
			}
		}

		bool ControllerManager::Destroy()
		{
			// Clean the physics objects
			Node<IController> * ptr = m_pControllers->GetHead();
			IController * removeController = nullptr;
			while ( ptr != nullptr )
			{
				removeController = ptr->GetData();
				assert( removeController );
				ptr = m_pControllers->Remove( ptr );
				delete removeController;
			}
			// Delete the physicsInfo's manager
			delete m_pControllers;
			m_pControllers = nullptr;

			DEBUG_PRINT( "The controller manager destoried succuessfully!" );
			return true;
		}
	}
}