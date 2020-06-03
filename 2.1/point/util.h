#ifndef UTILITARY_H
#define UTILITARY_H

#include <vector>
#include <string>
#include "point2d.h"

void randomToFile(std::string fname,unsigned int count);

bool fequal(float f1,float f2);

std::vector<point> fromFile(std::string filename,errno_t& error);

float fromSquareOneSide(point p1,point p2,point p3,point p4);

void saver();
#endif // UTILITARY_H
