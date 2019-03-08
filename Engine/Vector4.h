#pragma once
namespace Engine
{
	struct Vector3;

	struct Vector4
	{
	public:
		Vector4();
		Vector4( float i_x, float i_y, float i_z, float i_w );
		Vector4( const Vector4 & );
		Vector4 & operator=( const Vector4 & );
		~Vector4();
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};
}
