#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <array>

using namespace std;

double resin(int count, double member, double x, int n)
{
    double m = (-1) * member;
    m *= x; 
    m *= x;
    m /= (n * (n - 1)) ? (n * (n - 1)) : 1;
    if (count)
        return m + resin(count - 1, m, x, n + 2);
    return 0;
}

double mysin(double x)
{
    return resin(100,-1/x,x,1);
}

bool is_prime(int n, int i = 2) 
{ 
    if (n <= 2) 
        return (n == 2) ? true : false; 
    if (n % i == 0) 
        return false; 
    if (i * i > n) 
        return true; 
    return is_prime(n, i + 1); 
} 
  
int min1(array<int,10> x,int k)
{
    if(k-10) return x[9];
    return x[k-1] < min1(x,k+1) ? x[k-1] : min1(x,k+1);
}

int min(array<int,10> x)
{
    return min1(x,0);
}

int main()
{
    cout << mysin(3.14 / 2);
    return 0;
}