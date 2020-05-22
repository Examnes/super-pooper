#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float f(float x)
{
    if(x > 4) return (sin(x)+1)/(x+1);
    if(x > 2) return exp(-x);
    if(x > -1) return x*x;
    return abs(x-1)/(2*x);
}

int main(int, char**) 
{
    fstream fin("In.txt");
    float x;
    fin >> x;
    fin.close();

    cout << "f(x) = " << f(x) << endl;

    ofstream fout("Out.txt");
    fout << f(x); 
    fout.close();
    
    return 0;
}
