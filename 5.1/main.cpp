#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <chrono>
using namespace std;

int main(int argc,char** argv)
{
    // 2
    int N = 0;
    cout << "Введите N." << endl;
    cin >> N;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> N;
    }
    uint16_t length;
    ifstream fin("Input.txt");
    ofstream fout("Output.txt");
    fin >> length;
    int left;
    fin >> left;
    int middle;
    fin >> middle;
    int right;
    fin >> right;
    if(left + middle == N) fout << left << " ";
    for(uint16_t i = 0;i < length - 2;i++)
    {
        left = middle;
        middle = right;
        fin >> right;
        if(left + middle + right == N) fout << middle << " ";
    }
    if(middle + left == N) fout << left;
    fin.close();
    fout.close();
}