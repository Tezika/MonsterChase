#pragma once
#include "Point2D.h"

namespace Engine
{
	struct AABB
	{
	public:
		AABB(){};
		~AABB(){};
		AABB( const Point2D<float> & i_center, const Point2D<float> & i_extends );
		AABB( const AABB & i_other );
		void operator=( const AABB & i_other );

		Point2D<float> center;
		Point2D<float> extends;
	};
}