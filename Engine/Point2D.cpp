#include "stdafx.h"
#include "Point2D.h"


Point2D::Point2D()
{
	Point2D(0, 0);
}

Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y= y;
}

Point2D::~Point2D()
{

}

Point2D& Point2D::operator=(const Point2D& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Point2D& Point2D::operator+=(const Point2D& other)
{
	this->x = other.x + this->x;
	this->y = other.y + this->y;
	return *this;
}

Point2D& Point2D::operator-=(const Point2D& other)
{
	this->x = other.x+ this->x;
	this->y = other.y + this->y;
	return *this;
}


