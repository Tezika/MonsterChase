#include "stdafx.h"
#include <crtdbg.h>
#include <assert.h>
#include "Point2D.h"

bool Point2D_UnitTest()
{
	using namespace Engine;
	const Point2D<int> point_1(1, 2);
	const Point2D<int> point_2(3, 2);
	const Point2D<int> point_3(1, 2);
	Point2D<int> point_4;

	assert(point_1 != point_2);
	assert(point_1 == point_3);

	point_4 += point_3;
	assert(point_1 == point_4);

	printf("Congrat! It passed this unit test.");
	return true;
}