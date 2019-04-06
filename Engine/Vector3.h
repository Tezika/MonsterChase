#pragma once
namespace Engine
{
	struct Vector3
	{
	public:
		static Vector3 Zero;
		static Vector3 Up;
		static Vector3 Right;
		static Vector3 Forward;

		Vector3();
		Vector3( float i_x, float i_y, float i_z );
		Vector3( const Vector3 & i_other );
		void operator=( const Vector3 & i_other );

		Vector3 operator+( const Vector3 & i_other );
		void  operator+=( const Vector3 & i_other );

		Vector3 operator-( const Vector3 & i_other );
		void operator-=( const Vector3 & i_other );

		Vector3 operator*( float value );
		void operator*=( float value );

		Vector3 operator/( float value );
		void operator/=( float value );

		float Dot( const Vector3 & i_other );

		Vector3 Cross( const Vector3 & i_other );

		float Length();

		float Distance( const Vector3 & i_other );

		Vector3 Normalize();

		void Printout();

		~Vector3();

		float x;
		float y;
		float z;
	};

	inline Vector3 operator+( const Vector3 & i_lvc, const Vector3 & i_rvc )
	{
		return Vector3( i_lvc.x + i_rvc.x, i_lvc.y + i_rvc.y, i_lvc.z + i_rvc.z );
	}

	inline Vector3 operator-( const Vector3 & i_lvc, const Vector3 & i_rvc )
	{
		return Vector3( i_lvc.x - i_rvc.x, i_lvc.y - i_rvc.y, i_lvc.z - i_rvc.z );
	}
};