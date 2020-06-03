#ifndef POINT_2D_H
#define POINT_2D_H
#include <iostream>

class point
{
public:
    point();
    point(float _x,float _y);
    point point::operator+(const point& p2);
    bool point::operator==(const point& p2);
    float distance(point p2);
    friend std::ostream& operator<<(std::ostream& os, const point& p);
    float x;
    float y;  
};

#endif