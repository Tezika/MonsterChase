#pragma once

struct Point2D
{
	Point2D();
	Point2D(int x, int y);

	Point2D(const Point2D&);

	Point2D& operator=(const Point2D&);
	Point2D& operator+=(const Point2D&);
	Point2D& operator-=(const Point2D&);

	~Point2D();

	int x;
	int y;
};

inline bool operator==(const Point2D& lhs, const Point2D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Point2D& lhs, const Point2D& rhs)
{
	return lhs.x != rhs.x || lhs.y != rhs.y;
}


