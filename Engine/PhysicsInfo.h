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
			PhysicsInfo(){};
			PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo, Point2D<float> i_oDirOfForce );
			~PhysicsInfo();

			inline GameObject * GetGameObject(){ return m_pGo; }

			inline Point2D<float> GetDirOfForce(){ return m_dirOfForce; };
			inline void SetDirOfForce( const Point2D<float> & i_oForceOfDir ){ m_dirOfForce = i_oForceOfDir; };

			inline float GetMass(){ return m_mass; };
			inline float GetDrag(){ return m_drag; };

		private:
			GameObject * m_pGo;
			Point2D<float> m_dirOfForce;
			float m_mass;
			float m_drag;
		};
	}
}
