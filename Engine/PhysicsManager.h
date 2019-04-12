#pragma once
#include "SmartPtr.h"

namespace Engine
{
	class GameObject;

	template<typename T>
	class TList;

	struct AABB;

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

			bool CheckCollision( SmartPtr<GameObject> pGoA, SmartPtr<GameObject> pGoB,
				AABB * pABB, AABB * pBBB,
				float tFrameEnd,
				float & tOpenEarilest,
				float & tCloseLatest
			);

			bool CheckAxisCollision(
				float aExtendsXinAxis,
				float aExtendsYInAxis,
				float bBBExtendsInAxis,
				float bBBCenterInAxis,
				float aBBcenterInAxis,
				float velAInBInAxis,
				float tFrameEnd,
				float & tOpenEarilest,
				float & tCloseLatest
			);
		};
	}
}