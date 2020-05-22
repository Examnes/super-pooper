#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
using namespace std;

int N = 8;
float a = (float)M_PI;
float xbegin = -4.0f;
float xend = 4.0f;

float f(float x)
{
    return (sin(a*x)+sin(a)*sin(a))/(4+sin(x)*sin(x));
}

int main(int, char**) 
{
    int choise;
    cout << "������� ������ ��������" << endl 
         << "1.���� � ������������" << endl 
         << "2.���� � ������������" << endl 
         << "3.���� � ����������" << endl;
    cin >> choise;

    while( (cin.fail()) || (choise < 1) || (choise > 3) )
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> choise;
    }

    cout << "������� N" << endl;
    while( (cin.fail()) || (N < 0) )
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> N;
    }

    cout << "������� a" << endl;
    while( (cin.fail()))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> a;
    }

    cout << "������� ������ �������" << endl;
    while( (cin.fail()) || (N < 0) )
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> xbegin;
    }

    cout << "������� ����� �������" << endl;
    while( (cin.fail()) || (N < 0) )
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> xend;
    }

    ofstream fout("Out.txt");
    cout << setprecision(3) << fixed << "x\ty" << endl;
    fout << setprecision(3) << fixed << "x\ty" << endl;
    float x = xbegin;
    switch (choise)
    {
    case 1:
        while (x < xend)
        {
            cout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
            fout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
            x += (xend-xbegin)/N;
        }
        break;
    case 2:
        do
        {
            cout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
            fout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
            x += (xend-xbegin)/N;
        }while (x < xend);
        break;
    case 3:
        for(float x = xbegin;x < xend;x += (xend-xbegin)/N) 
        {
            cout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
            fout << x << "\t" << (abs(f(x)) < 0.01f  ? 0 : f(x)) << endl;
        }
        break;
    }
    

    return 0;
}
