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
#include "RenderInfo.h"
#include "RenderManager.h"

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
					tCloseLatest = -1.0f;
					tOpenEarilest = 100.0f;// However, this is a magic number :<.

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

#if defined(_DEBUG) && defined(_DrawDebugInfoWhileColliding)
			ptr = this->m_pPhysicsInfos->GetHead();
			while ( ptr != nullptr )
			{
				pPhysicsA = ptr->GetData();
				pCachedGo = pPhysicsA->GetGameObject();
				Render::RenderInfo * pRenderInfo = Render::RenderManager::GetInstance().GetRealRenderInfoByGameObject( pCachedGo );
				Render::RenderInfo * pDebugRenderInfo = Render::RenderManager::GetInstance().GetDebugRenderInfoByGameObject( pCachedGo );
				// If the object is in collision, it'll render the debug sprite
				if ( pPhysicsA->GetInCollision() )
				{
					pRenderInfo->SetRenderable( false );
					pDebugRenderInfo->SetRenderable( true );
				}
				// If the object is not in collision, it'll render the normal sprite.
				else
				{
					pRenderInfo->SetRenderable( true );
					pDebugRenderInfo->SetRenderable( false );
				}
				ptr = ptr->GetNext();
			}
			pCachedGo = nullptr;
#endif
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
			Matrix4x4 mtx_BToWorld = pGoB->GetMatrixFromLocalToWorld();

			// Calculate the B's collision axis in world
			// For X
			Vector4 CollisionAxisXInW = mtx_BToWorld * Vector4::UnitX;

			// Project the BoundingBox's center onto the collision axis in the world
			Vector4 ABBCenterInW = mtx_AToWorld * Vector4( pABB->center.m_x, pABB->center.m_y, 0, 1.0f );
			Vector4 BBBCenterInW = mtx_BToWorld * Vector4( pBBB->center.m_x, pBBB->center.m_y, 0, 1.0f );
			float ABBCenterOntoWX = Dot( ABBCenterInW, CollisionAxisXInW );
			float BBBCenterOntoWX = Dot( BBBCenterInW, CollisionAxisXInW );

			// Project the extends onto the collision axis in the world
			Vector4 ABBExtendsXInW = mtx_AToWorld * Vector4::UnitX * pABB->extends.m_x;
			Vector4 ABBExtendsYInW = mtx_AToWorld * Vector4::UnitY * pABB->extends.m_y;
			Vector4 BBBExtendsXInW = mtx_BToWorld * Vector4::UnitX * pBBB->extends.m_x;
			Vector4 BBBExtendsYInW = mtx_BToWorld * Vector4::UnitY * pBBB->extends.m_y;

			float AProjectedExtendsX = fabs( Dot( ABBExtendsXInW, CollisionAxisXInW ) ) + fabs( Dot( ABBExtendsYInW, CollisionAxisXInW ) );
			float BProjectedExntedsX = fabs( Dot( BBBExtendsXInW, CollisionAxisXInW ) ) + fabs( Dot( BBBExtendsYInW, CollisionAxisXInW ) );

			// Calculate the velocity onto the axis
			float AVelAlongXInW = Dot( Vector4( pGoA->GetVelocity(),0.0f), CollisionAxisXInW );
			float BVelAlongXInW = Dot( Vector4( pGoB->GetVelocity(), 0.0f ), CollisionAxisXInW );

			// Check for X axis
			bool bCollided = true;
			bCollided = this->CheckAxisCollision( 
				AProjectedExtendsX,
				BProjectedExntedsX,
				BBBCenterOntoWX,
				ABBCenterOntoWX,
				AVelAlongXInW - BVelAlongXInW,
				tFrameEnd,
				tOpenEarilest,
				tCloseLatest
			);
			if ( !bCollided )
			{
				return false;
			}
			Vector4 CollisionAxisYInW = mtx_BToWorld * Vector4::UnitY;

			// Recalculate bb's center onto axis
			float ABBCenterOntoWY = Dot( ABBCenterInW, CollisionAxisYInW );
			float BBBCenterOntoWY = Dot( BBBCenterInW, CollisionAxisYInW );

			// ReCalculate bbs' extends onto axis
			float AProjectedExtendsY = fabs( Dot( ABBExtendsXInW, CollisionAxisYInW ) ) + fabs( Dot( ABBExtendsYInW, CollisionAxisYInW ) );
			float BProjectedExntedsY = fabs( Dot( BBBExtendsXInW, CollisionAxisYInW ) ) + fabs( Dot( BBBExtendsYInW, CollisionAxisYInW ) );

			// Recalculate velocities
			float AVelAlongYInW = Dot( Vector4( pGoA->GetVelocity(), 0.0f ), CollisionAxisYInW );
			float BVelAlongYInW = Dot( Vector4( pGoB->GetVelocity(), 0.0f ), CollisionAxisYInW );

			// Check for Y axis
			bCollided = true;
			bCollided = this->CheckAxisCollision(
				AProjectedExtendsY,
				BProjectedExntedsY,
				BBBCenterOntoWY,
				ABBCenterOntoWY,
				AVelAlongYInW - BVelAlongYInW,
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
			float aBBExtendsProjectedOntoAxis,
			float bBBExtendsOntoAxis,
			float bBBCenterOntoAxis,
			float aBBCenterOntoAxis,
			float velARelBOnAxis,
			float tFrameEnd,
			float & tOpenEarilest,
			float & tCloseLatest
		)
		{
			// Check for X axis
			float bExtends = bBBExtendsOntoAxis + aBBExtendsProjectedOntoAxis;
			float bLeft = bBBCenterOntoAxis - bExtends;
			float bRight = bBBCenterOntoAxis + bExtends;

			float dClose = bLeft - aBBCenterOntoAxis;
			float dOpen = bRight - aBBCenterOntoAxis;

			float tOpen = 0;
			float tClose = 0;

			// When the realtive velocity projection is zero
			if ( velARelBOnAxis == 0.0f )
			{
				// If A's bb center outside the Bleft ~ bRight, there is no collision. 
				if ( aBBCenterOntoAxis < bLeft || aBBCenterOntoAxis > bRight )
				{
					return false;
				}
			}
			else
			{
				tOpen = dOpen / velARelBOnAxis;
				tClose = dClose / velARelBOnAxis;
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