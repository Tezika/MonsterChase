#include "stdafx.h"
#include "AABB.h"

namespace Engine
{
	AABB * AABB::Create( float i_center_x, float i_center_y, float i_exntends_x, float i_exntends_y )
	{
		return new AABB( i_center_x, i_center_y, i_exntends_x, i_exntends_y );
	}

	AABB * AABB::Create( const Point2D<float> & i_center, const Point2D<float> & i_extends )
	{
		return new AABB( i_center, i_extends );
	}

	AABB::AABB( const Point2D<float> & i_center, const Point2D<float> & i_extends ) :
		center( i_center ),
		extends( i_extends )
	{

	}

	AABB::AABB( const AABB & i_other ) :
		center( i_other.center ),
		extends( i_other.extends )
	{

	}

	AABB::AABB( float i_center_x, float i_center_y, float i_extends_x, float i_extends_y ) :
		center( Point2D<float>( i_center_x, i_center_y ) ),
		extends( Point2D<float>( i_extends_x, i_center_y ) )
	{

	}

	void AABB::operator=( const AABB & i_other )
	{
		this->center = i_other.center;
		this->extends = i_other.extends;
	}
}