#pragma once
namespace Engine
{
	struct Vector3
	{
	public:
		Vector3();
		Vector3( float i_x, float i_y, float i_z );
		~Vector3();
	private:
		float m_x;
		float m_y;
		float m_z;
	};
};