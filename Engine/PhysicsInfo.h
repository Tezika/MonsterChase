#pragma once
#include "SmartPtr.h"
#include "Vector3SSE.h"
#include "Delegate.h"

namespace Engine
{
	struct AABB;
	class GameObject;

	namespace Physics
	{
		class PhysicsInfo
		{
		public:
			static PhysicsInfo * Create( float i_mass, float i_dragness, bool i_bCollidable, bool i_bReflectable, SmartPtr<GameObject> i_pGo, AABB * i_pAABB );
			~PhysicsInfo();

			PhysicsInfo( const PhysicsInfo & );
			void operator=( const PhysicsInfo & );

			inline SmartPtr<GameObject> GetGameObject() const{ return m_pGo; }

			inline const Vector3SSE & GetDrivingForce(){ return m_force; }
			inline void SetDrivingForce( const Vector3SSE & i_oForce ){ m_force = i_oForce; };

			inline float GetMass() const { return m_mass; }
			inline float GetDragness() const { return m_dragness; }

			inline AABB * GetAABB(){ return m_pAABB; }
			inline void SetAABB( AABB * i_pAABB ){ m_pAABB = i_pAABB; }

			inline bool GetIsCollision(){ return m_bIsCollision; };
			inline void SetIsCollision( bool i_inCollision ){ m_bIsCollision = i_inCollision; };

			inline bool GetCollidable() { return m_bCollidable; }
			inline void SetCollidable( bool i_bCollidable ){ m_bCollidable = i_bCollidable; }

			inline bool IsReflectable(){ return m_bReflectable; }
			inline void SetReflectable( bool i_bReflectable ){ m_bReflectable = i_bReflectable; }

			void OnCollision();
		private:
			PhysicsInfo(){};
			PhysicsInfo( float i_mass, float i_drag, bool i_bCollidable, bool i_bReflectable, SmartPtr<GameObject> i_pGo, AABB * i_pAABB );
			SmartPtr<GameObject> m_pGo;
			Vector3SSE m_force;
			AABB * m_pAABB;
			float m_mass;
			float m_dragness;
			bool m_bIsCollision;
			bool m_bCollidable;
			bool m_bReflectable;
			Messaging::Delegate<> m_collisionDelegate;
		};
	}
}
