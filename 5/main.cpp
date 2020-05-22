#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <chrono>
using namespace std;

int main(int argc,char** argv)
{
    // 1
    srand((uint32_t)time(NULL));
    uint8_t length = rand() % 20 + 10;
    cout << "Введите Y если хотите заполнить с клавиатуры." << endl;
    char answer = getchar();
    ofstream outf("Input.txt");
    outf << (int)length << " ";
    uint8_t positve = 0,negative = 0,zero = 0;
    if(answer == 'Y')
    {
        for(int i = 0;i < length;i++)
        {
            int x = 0;
            cin >> x;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                cin >> x;
            }
            outf << x << " ";
            if(x > 0){positve++;}
            else if(x < 0){negative++;}
            else zero++;
        }
    }else
    {
        for(int i = 0;i < length;i++)
        {
            int x = (rand() - RAND_MAX / 2) % 5;
            outf << x << " ";
            if(x> 0){positve++;}
            else if(x < 0){negative++;}
            else zero++;
        }
    }
    outf.close();
    cout << "Количество положительных: "  << (int)positve << endl;
    cout << "Количество отрицательных: "  << (int)negative << endl;
    cout << "Количество нулевых: "  << (int)zero << endl;
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
    // 3
    fin.open("Output.txt");
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