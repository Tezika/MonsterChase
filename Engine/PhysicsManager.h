#pragma once
#include <ReferenceCounting/SmartPtr.h>
#include "CollisionPair.h"

namespace Engine
{
	class GameObject;

	template<typename T>
	class TList;
	struct AABB;
	struct Vector3;

	namespace Physics
	{
#ifndef _DrawDebugInfoWhileColliding
		//#define _DrawDebugInfoWhileColliding
#endif // !_DrawDebugInfo
		class PhysicsInfo;

		class PhysicsManager
		{
		public:
			static PhysicsManager& GetInstance()
			{
				static PhysicsManager instance;
				return instance;
			}
			PhysicsManager( PhysicsManager const& ) = delete;
			void operator=( PhysicsManager const& ) = delete;

			bool AddPhysicsObject( PhysicsInfo * i_pInfo );
			bool RemovePhysicsObject( GameObject * i_pGo );

			PhysicsInfo * GetInfoByGameObject( SmartPtr<GameObject> i_pGo );

			// Schedule functions
			bool Initialize();
			void Simulate( float i_dt );
			bool Destroy();

			// Collision check without SSE
			bool IsCollision(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_dt,
				float & i_collisionTime,
				Vector3 & i_collisionNormal
			);


			// Collision Check SSE version
			bool IsCollisionSSE(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_dt,
				float & i_collisionTime,
				Vector3SSE & i_collisionNormal
			);

		private:
			PhysicsManager() {};
			TList<PhysicsInfo> * m_pPhysicsInfos;

			bool CheckCollisionSSE(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_tFrameEnd,
				float & i_tOpenEarilest,
				float & i_tCloseLatest,
				Vector3SSE & i_collisionAxis
			);

			bool CheckAxisCollisionSSE(
				float aBBExtendsProjectedOntoAxis,
				float bBBExtendsOntoAxis,
				float bBBCenterOntoAxis,
				float aBBCenterOntoAxis,
				float velARelBOnAxis,
				float tFrameEnd,
				float & tOpenEarilest,
				float & tCloseLatest,
				const Vector3SSE & i_currentAxis,
				Vector3SSE & i_collisionAxis
			);


			bool CheckCollision(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_tFrameEnd,
				float & i_tOpenEarilest,
				float & i_tCloseLatest,
				Vector3 & i_collisionAxis
			);

			bool CheckAxisCollision(
				float aBBExtendsProjectedOntoAxis,
				float bBBExtendsOntoAxis,
				float bBBCenterOntoAxis,
				float aBBCenterOntoAxis,
				float velARelBOnAxis,
				float tFrameEnd,
				float & tOpenEarilest,
				float & tCloseLatest,
				const Vector3 & i_currentAxis,
				Vector3 & i_collisionAxis
			);

			CollisionPair * GetEarliestCollisionPair();

			TList<CollisionPair> * m_pCollisionPairs;

			void SimulateMovement( float i_dt );
			void SimulateCollision( float i_dt, TList<CollisionPair> * i_pCollisionPairs );

			void RecalculateVelByMomentum(
				const PhysicsInfo * pPhysicsInfoA, const PhysicsInfo * pPhysicsInfoB,
				const Vector3SSE & velA_dir, const Vector3SSE & velB_dir
			);

			void ResolveCollision( const CollisionPair * pCollisionPair );
		};
	}
}