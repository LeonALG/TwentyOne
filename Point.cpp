#include <windows.h>
#include "Point.h"


Point::Point()
{
	CurrentPoint.X = 0;
	CurrentPoint.Y = 0;
}

Point::Point(int x, int y)
{
	CurrentPoint.X = x;
	CurrentPoint.Y = y;
}

Point::Point(const Point& obj)
{
	CurrentPoint = obj.CurrentPoint;
}

Point::~Point()
{

}

void Point::SetCoord(COORD Coord)
{
	CurrentPoint = Coord;
}

COORD Point::GetCoord()
{
	return CurrentPoint;
}
