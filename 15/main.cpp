#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <cmath>
#include <array>

using namespace std;

const float c_a = 5, c_b = 1, c_c = 2;

float f(float x, float a = c_a, float b = c_b, float c = c_c)
{
    if((a * x - b) < 0 || x < 0 || c < 0) throw "Недопустимое отрицательное значение";
    return sqrt(a * x - b) - log(x) / log(c);
}

double root(double a, double b, double epsilon)
{
    if(epsilon < 0) throw "Отрицательная точность";
    if(f(a)==f(b)) throw "Одинаковые знаки по обе границы промежутка";
    while (fabs(b - a) > epsilon)
    {
        a = b - (b - a) * f(b) / (f(b) - f(a));
        b = a - (a - b) * f(a) / (f(a) - f(b));
    }
    return  a;
}

int main()
{
    
    return 0;
}