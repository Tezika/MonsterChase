#pragma once
namespace Engine
{
	struct Vector3
	{
	public:
		Vector3();
		Vector3( float i_x, float i_y, float i_z );
		Vector3( const Vector3 & i_other );
		void  operator=( const Vector3 & i_other );

		Vector3 & operator+( const Vector3 & i_other );
		void  operator+=( const Vector3 & i_other );

		Vector3 & operator-( const Vector3 & i_other );
		void operator-=( const Vector3 & i_other );

		Vector3 & operator*( float value );
		void operator*=( float value );

		Vector3 & operator/( float value );
		void operator/=( float value );
		
		float Dot( const Vector3 & i_other );

		Vector3 Cross( const Vector3 & i_other );

		float Magnitude();

		float Distance( const Vector3 & i_other );

		inline Vector3 Normalize(){ return Vector3( *this / this->Magnitude() ); };

		~Vector3();

		float x;
		float y;
		float z;
	};
};