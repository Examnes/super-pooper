#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

template <typename T>
T read(bool (*predicate)(T, T), T arg = 0)
{
    T x = 0;
    cin >> x;
    while ((cin.fail()) || !predicate(x, arg))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> x;
    }
    return x;
}

template <typename T>
bool answer(T a, T b)
{
    return a >= 0 && a <= 5;
}

template <typename T>
bool all(T a, T b)
{
    return true;
}

template <typename T>
bool greather(T a, T arg)
{
    return a > arg;
}

template <typename T>
bool lower(T a, T arg)
{
    return a < arg;
}

template <typename T>
bool countable(T a, T arg)
{
    return a > 0  && a < 1000000;
}

void fill_file_with_random(string filename,size_t count,float random_begin,float random_end)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(random_begin, random_end); // rage 0 - 1
    
    ofstream file = ofstream(filename,ios::binary);
    float rand_range = random_end - random_begin;
    while(count)
    {
        float number = dis(e) ;
        file.write((char*)&number,sizeof(float));
        count--;
    }
    file.close();
}

void create_input()
{
    cout << "Введите количество чисел" << endl;
    size_t N = read<size_t>(countable);
    cout << "Введите начало диапазона" << endl;
    float begin = read<float>(all);
    cout << "Введите конец диапазона" << endl;
    float end = read<float>(greather,begin);
    fill_file_with_random("input.bin",N,begin,end);
}

void print_to_screen_or_file(string input_filename,string output_filename = "nofile")
{
    ifstream input = ifstream(input_filename,ios::binary);
    if(output_filename != "nofile")
    {
        ofstream output; output.open(output_filename);
        while (input.peek() != EOF)
        {
            float number;
            input.read((char*)&number,sizeof(float));
            output << number << " ";
        }
        output.close();
    }else
    {
        cout << "Содержимое файла " << input_filename << ": " << endl;
        while (input.peek() != EOF)
        {
            float number;
            input.read((char*)&number,sizeof(float));
            cout << number << "\t";
        }
    }
    cout << endl;
    input.close();
    
}

float find_max(string filename)
{
    ifstream input; input.open(filename,ios::binary);
    input.seekg(0);
    float max = 0;
    input.read((char*)&max,sizeof(float));
    while (input.peek() != EOF)
    {
        float number;
        input.read((char*)&number,sizeof(float));
        if(number > max) max = number;
    }
    input.close();
    return max;
}

float find_max_in_txt(string filename)
{
    ifstream input; input.open(filename);
    float max = 0;
    input >> max;
    while (input.peek() != EOF)
    {
        float number;
        input >> number;
        if(number > max) max = number;
    }
    input.close();
    return max;
}

void preform_to_output(string input_filename,string output_filename,float rel)
{
    float max = find_max(input_filename);
    ifstream input; input.open(input_filename,ios::binary);
    ofstream output; output.open(output_filename,ios::binary);
    while (input.peek() != EOF)
    {
        float number;
        input.read((char*)&number,sizeof(float));
        if(abs(number) > rel) number = number / (max / 2);
        output.write((char*)&number,sizeof(float));
    }
    input.close();
    output.close();
}

void replace(string filename,float rel)
{
    float max = find_max(filename);
    fstream file = fstream(filename, ios::in | ios::out);
    while (file.peek() != EOF)
    {
        float number;
        int pos = file.tellg();
        file.read((char*)&number,sizeof(float));
        if(abs(number) > rel)
        {
            file.seekp(pos);
            number = number / (max / 2);
            file.write((char*)&number,sizeof(float));
        }
    }
    file.close();
}

void txt_to_bin_preformed(string input_filename,string output_filename,float rel)
{
    float max = find_max_in_txt(input_filename);
    ifstream input; input.open(input_filename);
    ofstream output; output.open(output_filename,ios::binary);
    float number;
    while (input >> number)
    {
        if(abs(number) > rel) number = number / (max / 2);
        output.write((char*)&number,sizeof(float));
    }
    input.close();
    output.close();
}

bool compare_files(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);
    
    if (f1.tellg() != f2.tellg()) {
      return false;
    }

    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);

    while (f1.peek() != EOF)
    {
        float number;
        f1.read((char*)&number,sizeof(float));
        float number2;
        f2.read((char*)&number2,sizeof(float));
        if(number != number2) return false;
    }
    f1.close();
    f2.close();
    return true;
}

void append(const string& filename1, const string& filename2)
{
    ofstream file1(filename1, ifstream::app | ifstream::binary);
    ifstream file2(filename2, ifstream::binary);
    file1 << file2.rdbuf();
}

int main()
{
    system("chcp 65001");
    srand(time(0));
    cout << "Задание 1" << endl;
    create_input();//1
    system("pause");
    cout << "Задание 2" << endl;
    print_to_screen_or_file("input.bin");
    print_to_screen_or_file("input.bin","text1.txt");//2
    system("pause");
    cout << "Задание 3" << endl;
    cout << "Введите число для сравнения" << endl;
    float rel = read<float>(greather,0);
    preform_to_output("input.bin","output.bin",rel);//3
    system("pause");
    cout << "Задание 4" << endl;
    print_to_screen_or_file("output.bin");
    print_to_screen_or_file("output.bin","text2.txt");//4
    system("pause");
    cout << "Задание 5" << endl;
    append("input.bin","output.bin");//5
    system("pause");
    cout << "Задание 6" << endl;
    print_to_screen_or_file("input.bin");
    print_to_screen_or_file("input.bin","text3.txt");//6
    system("pause");
    cout << "Задание 7" << endl;
    cout << "Введите число для сравнения" << endl;
    rel = read<float>(greather,0);
    replace("input.bin",rel);//7
    system("pause");
    cout << "Задание 8" << endl;
    print_to_screen_or_file("input.bin");
    print_to_screen_or_file("input.bin","text4.txt");//8
    system("pause");
    cout << "Задание 9" << endl;
    cout << "Введите число для сравнения" << endl;
    rel = read<float>(greather,0);
    txt_to_bin_preformed("text4.txt","out2.bin",rel);//9
    system("pause");
    cout << "Задание 10" << endl;
    print_to_screen_or_file("out2.bin");
    print_to_screen_or_file("out2.bin","text5.txt");//10
    system("pause");
    cout << "Задание 11" << endl;
    if(compare_files("out2.bin","input.bin"))
    {
        cout << "Файлы совпадают" << endl;
    }else
    {
        cout << "Файлы не совпадают" << endl;
    }
    system("pause");
    return 0;
}