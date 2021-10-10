#pragma once

class Point
{
protected:
	COORD CurrentPoint;
public:
	Point();
	Point(const Point& obj);
	Point(int x, int y);
	virtual ~Point();
	void SetCoord(COORD Coord);
	COORD GetCoord();
};

