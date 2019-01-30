#pragma once

class GameObject;
namespace Physics
{
	class PhysicsInfo
	{
	public:
		PhysicsInfo(){};
		PhysicsInfo( float i_mass, float i_drag, GameObject * i_pGo );
		~PhysicsInfo();
	private:
		GameObject * m_pGo;
		float m_mass;
		float m_drag;
	};
}