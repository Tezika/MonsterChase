#pragma once
#include "Point2D.h"

namespace Engine
{
	class GameObject;

	namespace Physics
	{
		class PhysicsInfo
		{
		public:
			static PhysicsInfo * Create( float i_mass, float i_dragness, GameObject * i_pGo, Point2D<float> & i_oForce );
			~PhysicsInfo();

			PhysicsInfo( const PhysicsInfo & ) = delete;
			void operator=( const PhysicsInfo & ) = delete;

			inline GameObject * GetGameObject(){ return m_pGo; }

			inline const Point2D<float> & GetDrivingForce(){ return m_force; };
			inline void SetDrivingForce( const Point2D<float> & i_oForce ){ m_force = i_oForce; };

			inline float GetMass(){ return m_mass; };
			inline float GetDragness(){ return m_dragness; };

		private:
			PhysicsInfo(){};
			PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo, Point2D<float> & i_oForce );
			GameObject * m_pGo;
			Point2D<float> m_force;
			float m_mass;
			float m_dragness;
		};
	}
}
