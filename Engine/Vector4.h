#pragma once
namespace Engine
{
	struct Vector3;

	struct Vector4
	{
	public:
		static Vector4 Zero;
		static Vector4 UnitX;
		static Vector4 UnitY;
		static Vector4 UnitZ;
		static Vector4 UnitW;

		Vector4();
		Vector4( float i_x, float i_y, float i_z, float i_w );
		Vector4( const Vector3 & i_vct3, float i_w );
		Vector4( const Vector4 & );
		void operator=( const Vector4 & );

		Vector4 operator+( const Vector4 & i_other );
		void  operator+=( const Vector4 & i_other );

		Vector4 operator-( const Vector4 & i_other );
		void operator-=( const Vector4 & i_other );

		Vector4 operator*( float value );
		void operator*=( float value );

		Vector4 operator/( float value );
		void operator/=( float value );

		float Length();

		~Vector4();

		float x;
		float y;
		float z;
		float w;
	};
}
