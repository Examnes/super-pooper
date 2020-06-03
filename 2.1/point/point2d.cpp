#include "point2d.h"
#include <math.h>
#include "util.h"
#include <iostream>

point::point():x(),y()
{
}

point::point(float _x,float _y):x(_x),y(_y)
{
}

float point::distance(point p2)
{
    return sqrt((x-p2.x)*(x-p2.x)+(y-p2.y)*(y-p2.y));
}

point point::operator+(const point& p2)
{
    return point(x+p2.x,y+p2.y);
}

bool point::operator==(const point& p2)
{
    return fequal(x,p2.x)&fequal(y,p2.y);
}

std::ostream& operator<<(std::ostream& os, const point& p)
{
    os << "("<<p.x<<","<<p.y<<")";
    return os;
}