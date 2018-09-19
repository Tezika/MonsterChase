#include "stdafx.h"
#include "Point2D.h"


Point2D::Point2D()
{
	Point2D(0, 0);
}

Point2D::Point2D(int x, int y)
{
	x_ = x;
	y_ = y;
}

Point2D::~Point2D()
{

}

Point2D& Point2D::operator=(const Point2D& other)
{
	this->x_ = other.x_;
	this->y_ = other.y_;
	return *this;
}

Point2D& Point2D::operator+=(const Point2D& other)
{
	this->x_ = other.x_ + this->x_;
	this->y_ = other.y_ + this->y_;
	return *this;
}

Point2D& Point2D::operator-=(const Point2D& other)
{
	this->x_ = other.x_ + this->x_;
	this->y_ = other.y_ + this->y_;
	return *this;
}

Point2D Point2D::operator+(const Point2D& other)
{
	Point2D res;
	res.x_ = this->x_ + other.x_;
	res.y_ = this->y_ + other.y_;
	return res;
}

Point2D Point2D::operator-(const Point2D& other)
{
	Point2D res;
	res.x_ = this->x_ - other.x_;
	res.y_ = this->y_ - other.y_;
	return res;
}

bool Point2D::operator==(const Point2D& other)
{
	return (this->x_ == other.x_ && this->y_ == other.y_);
}

bool Point2D::operator!=(const Point2D& other)
{
	return this->x_ != other.x_ || this->y_ != other.y_;
}