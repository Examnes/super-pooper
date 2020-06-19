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

double f(double x)
{
    return x*x;
}

double g(double x)
{
    return x + 9;
}

double trap_int_ref(double a, double b, int n, double (&func)(double))
{
    const double width = (b - a) / n;

    double trap = 0;
    for (int step = 0; step < n; step++)
    {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        trap += 0.5 * (x2 - x1) * (func(x1) + func(x2));
    }

    return trap;
}

double trap_int_ptr(double a, double b, int n, double (*func)(double))
{
    const double width = (b - a) / n;

    double trap = 0;
    for (int step = 0; step < n; step++)
    {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        trap += 0.5 * (x2 - x1) * (func(x1) + func(x2));
    }

    return trap;
}

int main()
{
    cout << trap_int_ref(0,3,100,f) + trap_int_ptr(3,6,100,g) << endl;
    return 0;
}