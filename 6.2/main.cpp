#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <memory.h>
using namespace std;

template <typename T>
T read(bool (*predicate)(T, T), T arg = 0)
{
    T x = 0;
    cin >> x;
    while ((cin.fail()) || !predicate(x, arg))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cin >> x;
    }
    return x;
}

template <typename T>
bool answer(T a, T b)
{
    return a >= '0' && a <= '3';
}

template <typename T>
bool all(T a, T b)
{
    return true;
}

bool is_full_square(uint32_t a)
{
    return (sqrt(a) == floor(sqrt(a)));
}

bool isFibonacci(uint32_t n)
{
    return is_full_square(5 * n * n + 4) ||
           is_full_square(5 * n * n - 4);
}

void start()
{
    system("chcp 1251");
    cout << "��� ��������� ��������� ������ �������� ��� ������� �������. ��� �������� ���������� ����� ����� ��������� ����� ����������� �� ������ ���������, ���� ������������ �� �������� �������� ������� ����� ����� ��������� ��� ���� � ������ ����� ��� ������ ���������.\n";
    cout << "��� �������� �������� ��������� ������ ��� �����, ������� ����, ��� ������ ������������, � ��� �� ��������� ������� ������������ �������.\n";
}

void print_array(uint32_t *arr, size_t sz)
{
    cout << "{";
    if (sz)
        for (size_t i = 0; i < sz - 1; i++)
            cout << arr[i] << ", ";
    cout << arr[sz - 1] << "}\n";
}

void insert_after_fibonacci(uint32_t*& arr,uint32_t element,size_t& sz)
{
    size_t new_size = sz;
    for_each(arr, arr + sz, [&new_size](uint32_t a) { if(isFibonacci(a)) new_size++; });
    uint32_t* temp = new uint32_t[new_size];
    size_t ptr = 0;
    for (size_t i = 0; i < sz; i++)
    {
        temp[ptr++] = arr[i];
        if (isFibonacci(arr[i]))
        {
            temp[ptr++] = element;
        }
    }
    delete arr;
    arr = new uint32_t[new_size];
    memcpy(arr, temp, new_size * sizeof(uint32_t));
    delete temp;
    sz = new_size;
}

bool insert_after_min_full_square(uint32_t*& arr,uint32_t element,size_t& sz)
{
    int max = -1;
    size_t index = 0;
    uint32_t* temp;
    for (size_t i = 0; i < sz; i++)
    {
        if (is_full_square(arr[i]))
        {
            cout << arr[i] << max << endl;
            if ((int)arr[i] > max)
            {
                max = arr[i];
                index = i;
            }
        }
    }
    if (max > 0)
    {
        temp = new uint32_t[sz + 1];
        memcpy(temp, arr, index * sizeof(uint32_t));
        temp[index + 1] = element;
        memcpy(temp + index + 2, arr, (sz - index) * sizeof(uint32_t));
        delete arr;
        arr = new uint32_t[sz + 1];
        memcpy(arr, temp, (sz + 1) * sizeof(uint32_t));
        sz++;
        delete temp;
    }
    return true;
}

void remove_dividable(uint32_t*& arr,size_t& sz)
{
    uint32_t* temp;
    uint32_t a = read<uint32_t>(all);
    size_t new_size = 0;
    for(size_t i = 0;i < sz;i++)
    {
        if(arr[i] % a) new_size++;
    }
    temp = new uint32_t[new_size];
    size_t ptr = 0;
    for (int i = 0; i < sz; i++)
    {
        if (arr[i] % a != 0)
            temp[ptr++] = arr[i];
    }
    delete arr;
    arr = new uint32_t[new_size];
    memcpy(arr, temp, new_size * sizeof(uint32_t));
    delete temp;
    sz = new_size;
}

int main()
{
    start();
    char user_answer;
    size_t sz = 0;
    uint32_t *arr = new uint32_t[200];
    cout << "Y ���� ������ ������� �� input.txt\n";
    user_answer = read<char>(all);
    if (tolower(user_answer) == 'y')
    {
        size_t ptr = 0;
        ifstream file("input.txt");
        uint32_t datam;
        file >> datam;
        arr[ptr++] = datam;
        while (!file.eof())
        {
            file >> datam;
            arr[ptr++] = datam;
        }
        sz = ptr;
    }
    user_answer = 0;

    uint32_t *temp;

    user_answer = 0;
    do
    {
        cout
            << "��������:" << endl
            << "1.�������" << endl
            << "2.��������(1.1 1.2)" << endl
            << "3.������� (2)" << endl
            << "0.�����" << endl;

        char user_answer = read<char>(answer);
        switch (user_answer)
        {
        case '1':
            print_array(arr, sz);
            break;
        case '2':
        {
            cout << "������� ��� ���������." << endl;
            uint32_t element = read<uint32_t>(all);
            cout << "Y ���� ��������� ����� ����� ��������, ����� ����� ����������� ������� ��������." << endl;
            char opinion = read<char>(all);
            if (tolower(opinion) == 'y')
            {
                insert_after_fibonacci(arr,element,sz);
            }   
            else
            {
                insert_after_min_full_square(arr,element,sz);
            }
        }
        break;
        case '3':
        {
            cout << "������� ������� ���� �������." << endl;
            uint32_t a = read<uint32_t>(all);
            remove_dividable(arr,sz);
        }
        case '0':
            cout << "exit" << endl;
            return 0;
            break;
        }
    } while (user_answer != '0');

    return 0;
}