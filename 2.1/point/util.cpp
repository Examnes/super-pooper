#include "util.h"
#include <fstream>
#include <limits>
#include <math.h>
#include <algorithm>
#include "point2d.h"

void randomToFile(std::string fname,unsigned int count)
{
    if(count)
    {
        std::ofstream file;
        file.open(fname);
        for(count;count;count--)
        {
            file<<(rand()/(RAND_MAX + 1.)-0.5)*10<<" ";
        }
        file.close();
    }
}

bool fequal(float f1,float f2)
{
    return std::abs(f1-f2) <= std::numeric_limits<float>::epsilon() * std::max(std::abs(f1), std::abs(f2)) * 10;
}

std::vector<point> fromFile(std::string filename,errno_t& error)
{
    std::ifstream file(filename);
    if(!file)
    {
        std::cout<<"Невозможно открыть файл."<<std::endl;
        error = 1;
        return std::vector<point>();
    }
    float* raw = new float[100000];
    int i = 0;
    while(!file.eof())
    {
        file>>raw[i];
        i++;
    }
    i-=i%2;
    if(i<8)
    {
        std::cout<<"В файле недостаточно точек чтобы построить квадрат."<<std::endl;
        error = 2;
        return std::vector<point>();
    }
    
    std::vector<point> v = std::vector<point>();
    for(int j = 0;j<i/2;j++)
    {
        point curpoint = point(raw[j*2],raw[j*2+1]);
        bool alreadyExists = false;
        for(int k = 0;k<v.size();k++)
        {
            if(v[k]==curpoint) alreadyExists = true;
        }
        if(!alreadyExists) v.push_back(curpoint);
    }
    delete [] raw;
    return v;
}

float fromSquareOneSide(point p1,point p2,point p3,point p4)
{
    float d1 = p1.distance(p2);
    float d2 = p2.distance(p3);
    float d3 = p3.distance(p4);
    float d4 = p4.distance(p1);
    
    point R = p1+p2+p3+p4;
    R.x = R.x/4;
    R.y = R.y/4;
    
    float r1 = R.distance(p2);
    float r2 = R.distance(p3);
    float r3 = R.distance(p4);
    float r4 = R.distance(p1);

    if( fequal(d1,d2)&fequal(d2,d3)&fequal(d3,d4)&fequal(d4,d1)&fequal(r1,r2)&fequal(r2,r3)&fequal(r3,r4)&fequal(r4,r1) )
    {
        return r1*2/((float)sqrt(2));
    }
    return 0;
}

void saver()
{
    std::cout<<"Данное программное обеспечение называется square2d,\n оно предназначено для поиска наибольшего квадрата,\n задаваемого точками из файла. Программа была разработана Тагировым Русланом."<<std::endl;
}