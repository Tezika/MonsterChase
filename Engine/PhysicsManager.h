#pragma once
#include "SmartPtr.h"
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
#define _DrawDebugInfoWhileColliding
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

		private:
			PhysicsManager() {};
			TList<PhysicsInfo> * m_pPhysicsInfos;

			bool IsCollision(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_dt,
				float & i_collisionTime,
				Vector3 & i_collisionNormal
			);

			bool CheckCollision(
				PhysicsInfo * i_pPhysicsInfoA,
				PhysicsInfo * i_pPhysicsInfoB,
				float i_tFrameEnd,
				float & i_tOpenEarilest,
				float & i_tCloseLatest
			);

			bool CheckAxisCollision(
				float aBBExtendsProjectedOntoAxis,
				float bBBExtendsOntoAxis,
				float bBBCenterOntoAxis,
				float aBBCenterOntoAxis,
				float velARelBOnAxis,
				float tFrameEnd,
				float & tOpenEarilest,
				float & tCloseLatest
			);

			TList<CollisionPair> * m_pCollisionPairs;

			void SimulateMovement( float i_dt);
			void SimulateCollision( float i_dt, float & i_tEarliestCollision, float & i_tProcess, TList<CollisionPair> * i_pCollisionPairs );
		};
	}
}