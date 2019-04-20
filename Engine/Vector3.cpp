#include "stdafx.h"
#include "Vector3.h"
#include "Assert.h"
#include "math.h"
#include "stdio.h"

namespace Engine
{
	Vector3 Vector3::Zero = Vector3( 0, 0, 0 );
	Vector3 Vector3::Up = Vector3( 0, 1, 0 );
	Vector3 Vector3::Right = Vector3( 1, 0, 0 );
	Vector3 Vector3::Forward = Vector3( 0, 0, 1 );

	Vector3::Vector3()
	{
	}

	Vector3::Vector3( float i_x, float i_y, float i_z )
		:x( i_x ), y( i_y ), z( i_z )
	{
	}

	Vector3::Vector3( const Vector3 & i_other )
		: x( i_other.x ), y( i_other.y ), z( i_other.z )
	{
	}

	void Vector3::operator=( const Vector3 & i_other )
	{
		this->x = i_other.x;
		this->y = i_other.y;
		this->z = i_other.z;
	}

	Vector3 Vector3::operator+( const Vector3 & i_other ) const
	{
		return Vector3( this->x + i_other.x, this->y + i_other.y, this->z + i_other.z );
	}

	void Vector3::operator+=( const Vector3 & i_other )
	{
		this->x += i_other.x;
		this->y += i_other.y;
		this->z += i_other.z;
	}

	Vector3 Vector3::operator-( const Vector3 & i_other ) const
	{
		return Vector3( this->x - i_other.x, this->y - i_other.y, this->z - i_other.z );
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3( -this->x, -this->y, -this->z );
	}

	void Vector3::operator-=( const Vector3 & i_other )
	{
		this->x -= i_other.x;
		this->y -= i_other.y;
		this->z -= i_other.z;
	}

	Vector3  Vector3::operator*( float value ) const
	{
		return Vector3( this->x * value, this->y * value, this->z * value );
	}

	void Vector3::operator*=( float value )
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
	}

	Vector3 Vector3::operator/( float value ) const
	{
		assert( value != 0 );
		return Vector3( this->x / value, this->y / value, this->z / value );
	}

	void Vector3::operator/=( float value )
	{
		assert( value != 0 );
		this->x /= value;
		this->y /= value;
		this->z /= value;
	}

	float Vector3::Dot( const Vector3 & i_other ) const
	{
		return this->x * i_other.x + this->y * i_other.y + this->z * i_other.z;
	}

	Vector3 Vector3::Cross( const Vector3 & i_other ) const
	{
		return Vector3(
			this->y * i_other.z - this->z * i_other.y,
			this->z * i_other.x - this->x * i_other.z,
			this->x * i_other.y - this->y * i_other.x
		);
	}

	float Vector3::Length() const
	{
		return sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	float Vector3::Distance( const Vector3 & i_other ) const
	{
		return sqrtf(
			( this->x - i_other.x ) * ( this->x - i_other.x ) +
			( this->y - i_other.y ) * ( this->y - i_other.y ) +
			( this->z - i_other.z ) * ( this->z - i_other.z )
		);
	}

	Vector3 Vector3::Normalize() const
	{
		float length = this->Length();
		if ( length == 0 )
		{
			return Vector3::Zero;
		}
		return Vector3( this->x / length, this->y / length, this->z / length );
	}

	Vector3 Vector3::OrthoNormalize( const Vector3 & tangent ) const
	{
		Vector3 normalTangent = tangent.Normalize();
		return this->Normalize().Cross( normalTangent );
	}

	void Vector3::Printout() const
	{
#ifdef _DEBUG
		printf( "x: %.5f, y: %.5f, z: %.5f\n", this->x, this->y, this->z );
#endif
	}

	Vector3::~Vector3()
	{
	}
}