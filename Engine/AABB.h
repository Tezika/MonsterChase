#pragma once
#include "Point2D.h"

namespace Engine
{
	struct AABB
	{
	public:
		static AABB * Create( float i_center_x, float i_center_y, float i_extends_x, float i_extends_y );
		static AABB * Create( const Point2D<float> & i_center, const Point2D<float> & i_extends );
		AABB(){};
		~AABB(){};
		AABB( float i_center_x, float i_center_y, float i_extends_x, float i_extends_y );
		AABB( const Point2D<float> & i_center, const Point2D<float> & i_extends );
		AABB( const AABB & i_other );
		void operator=( const AABB & i_other );

		Point2D<float> center;
		Point2D<float> extends;
	};
}