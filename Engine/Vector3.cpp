#include "stdafx.h"
#include "Vector3.h"
#include "Assert.h"
#include "math.h"

namespace Engine
{
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

	Vector3 & Vector3::operator+( const Vector3 & i_other )
	{
		this->x += i_other.x;
		this->y += i_other.y;
		this->z += i_other.z;
		return *this;
	}

	void Vector3::operator+=( const Vector3 & i_other )
	{
		this->x += i_other.x;
		this->y += i_other.y;
		this->z += i_other.z;
	}

	Vector3 & Vector3::operator-( const Vector3 & i_other )
	{
		this->x -= i_other.x;
		this->y -= i_other.y;
		this->z -= i_other.z;
		return *this;
	}

	void Vector3::operator-=( const Vector3 & i_other )
	{
		this->x -= i_other.x;
		this->y -= i_other.y;
		this->z -= i_other.z;
	}

	Vector3 & Vector3::operator*( float value )
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	void Vector3::operator*=( float value )
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
	}

	Vector3 & Vector3::operator/( float value )
	{
		assert( value != 0 );
		this->x /= value;
		this->y /= value;
		this->z /= value;
		return *this;
	}

	void Vector3::operator/=( float value )
	{
		assert( value != 0 );
		this->x /= value;
		this->y /= value;
		this->z /= value;
	}

	float Vector3::Dot( const Vector3 & i_other )
	{
		return this->x * i_other.x + this->y * i_other.y + this->z * i_other.z;
	}

	Vector3 Vector3::Cross( const Vector3 & i_other )
	{
		return Vector3( 
			this->y * i_other.z - this->z * i_other.y,
			this->z * i_other.x - this->x * i_other.z,
			this->x * i_other.y - this->y * i_other.x
		);
	}

	float Vector3::Magnitude()
	{
		return sqrt( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	float Vector3::Distance(const Vector3 & i_other)
	{
		Vector3 temp = *this - i_other;
		return temp.Magnitude();
	}

	Vector3::~Vector3()
	{
	}
}
