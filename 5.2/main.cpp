#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <chrono>
using namespace std;

int main(long argc,char** argv)
{
    // 3
    ifstream fin("Output.txt");
    int max = 0;
    while(!fin.eof())
    {
        int x;
        fin >> x;
        if(x > max) max = x;
    }
    if(max) {cout << "Максимальное среди чисел: " << max << endl;} else cout << "Положительных чисел нет " << endl;
    return 0;
}