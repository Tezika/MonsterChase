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

		Vector4 operator+( const Vector4 & i_other ) const;
		void  operator+=( const Vector4 & i_other );

		Vector4 operator-( const Vector4 & i_other ) const;
		void operator-=( const Vector4 & i_other );

		Vector4 operator-() const;

		Vector4 operator*( float value ) const;
		void operator*=( float value );

		Vector4 operator/( float value ) const;
		void operator/=( float value );

		float Length() const;

		void Printout() const;

		~Vector4();

		float x;
		float y;
		float z;
		float w;
	};

	inline float Dot( const Vector4 & i_lhs, const Vector4 & i_rhs )
	{
		return i_lhs.x * i_rhs.x + i_lhs.y * i_rhs.y + i_lhs.z * i_rhs.z + i_lhs.w * i_rhs.w;
	}
}
