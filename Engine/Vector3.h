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

		Vector3 operator+( const Vector3 & i_other ) const;
		void  operator+=( const Vector3 & i_other );

		Vector3 operator-( const Vector3 & i_other ) const;
		void operator-=( const Vector3 & i_other );

		Vector3 operator-() const;

		Vector3 operator*( float value ) const;
		void operator*=( float value );

		Vector3 operator/( float value ) const;
		void operator/=( float value );

		float Dot( const Vector3 & i_other ) const;

		Vector3 Cross( const Vector3 & i_other ) const;

		float Length() const;

		float Distance( const Vector3 & i_other ) const;

		Vector3 Normalize() const;

		Vector3 OrthoNormalize( const Vector3 & tangent ) const;

		Vector3 Reflect( const Vector3 &i_normal ) const;

		void Printout() const;

		~Vector3();

		float x;
		float y;
		float z;
	};

	inline Vector3 operator*( float value, const Vector3 & i_vct )
	{
		return i_vct * value;
	}
};