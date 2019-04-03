#include "stdafx.h"
#include "AABB.h"

namespace Engine
{
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

	void AABB::operator=( const AABB & i_other )
	{
		this->center = i_other.center;
		this->extends = i_other.extends;
	}
}