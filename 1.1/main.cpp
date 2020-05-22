#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
using namespace std;

float f1(float x)
{
    return (sin(x)+1)/(x+1);
}

float f2(float x)
{
    return exp(-x);
}

float f3(float x)
{
    return x*x;
}

float f4(float x)
{
    return abs(x-1)/(2*x);
}

int main(int, char**) 
{
    cout << "Введите номер формулы."<<endl;
    int choise = 0;
    cin >> choise;
    if((!cin.fail()) && (choise<=4) && (choise >= 1))
    {
    cout << "Введите x." << endl;
    float x;
    cin >> x;
    if(!cin.fail())
    switch (choise)
        {
        case 1:
        if ( (x - 1) > numeric_limits<float>::epsilon() * 100 ){ cout << "f(x) = " << f1(x) << endl;}
        else cout << "x не входит в область определения функции." << endl;
            break;
        case 2:
        cout << "f(x) = " << f2(x) << endl;
            break;
        case 3:
        cout << "f(x) = " << f2(x) << endl;
            break;
        case 4:
        if ( x > numeric_limits<float>::epsilon() * 100 ){ cout << "f(x) = " << f4(x) << endl;}
        else cout << "x не входит в область определения функции." << endl;
            break;
        }
    }else
    {
        cout << "Некорректный ввод." << endl;
    }
    
    
    
    return 0;
} 