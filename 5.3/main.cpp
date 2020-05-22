#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <chrono>
using namespace std;

template<typename T>
T read()
{
    T x = 0;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> x;
    }
    return x;
}

void write_to_file_and_make_stats(uint8_t& positve,uint8_t& negative,uint8_t& zero,bool user_input = false)
{
    uint32_t length = rand() % 20 + 10;
    ofstream outf("Input.txt");
    outf << length << " ";

    if(user_input)
    {
        for(uint32_t i = 0;i < length;i++)
        {
            int x = read<int>();
            outf << x << " ";
            if(x > 0){positve++;}
            else if(x < 0){negative++;}
            else zero++;
        }
        outf.close();
        return;
    }

    for(uint32_t i = 0;i < length;i++)
    {
        int x = (rand() - RAND_MAX / 2) % 10;
        outf << x << " ";
        if(x> 0){positve++;}
        else if(x < 0){negative++;}
        else zero++;
    }
    outf.close();
}

void read_file_and_write_situable(int N)
{
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

int find_max_positive_in_file()
{
    ifstream fin("Output.txt");
    int max = 0;
    while(!fin.eof())
    {
        int x;
        fin >> x;
        if(x > max) max = x;
    }
    return max;
}

int main(int argc,char** argv)
{
    cout << "Введите Y если хотите заполнить с клавиатуры." << endl;
    char answer = read<char>();
    uint8_t positve = 0,negative = 0,zero = 0;
    if(tolower(answer) == 'y')
    {
        write_to_file_and_make_stats(positve,negative,zero,true);
    }else
    {
        write_to_file_and_make_stats(positve,negative,zero);
    }
    cout << "Количество положительных: "  << (int)positve << endl;
    cout << "Количество отрицательных: "  << (int)negative << endl;
    cout << "Количество нулевых: "  << (int)zero << endl;
    
    cout << "Введите N" << endl;
    int N = read<int>();
    read_file_and_write_situable(N);

    int max = find_max_positive_in_file();
    if(max) {cout << "Максимальное среди чисел: " << max << endl;} 
        else cout << "Положительных чисел нет " << endl;

    return 0;
}