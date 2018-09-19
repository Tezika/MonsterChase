#pragma once
struct Point2D 
{
public:
	Point2D();
	Point2D(int x, int y);

	Point2D(const Point2D&);

	Point2D& operator=(const Point2D&);
	Point2D& operator+=(const Point2D&);
	Point2D& operator-=(const Point2D&);

	Point2D operator+(const Point2D&);
	Point2D operator-(const Point2D&);

	bool operator== (const Point2D&);
	bool operator!=(const Point2D&);

	inline int GetX() { return this->x_; }
	inline int GetY() { return this->y_; }

	~Point2D();

private:
	int x_;
	int y_;
};


