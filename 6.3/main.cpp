#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
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


template <typename T>
bool natural_non_zero(T a, T b)
{
    return a > 0;
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

void insert_after_fibonacci(vector<uint32_t>& arr,uint32_t element)
{
    for(size_t i = 0;i < arr.size();i++)
    {
        if(isFibonacci(arr[i]))
        {
            cout << arr[i] << endl;
            arr.insert(arr.begin()+i,element);
            i++;
        }
    }
}

void insert_after_min_full_square(vector<uint32_t>& arr,uint32_t element)
{
    int max = -1;
    size_t index = 0;
    uint32_t* temp;
    for (size_t i = 0; i < arr.size(); i++)
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
        arr.insert(arr.begin()+index,element);
    }
}

void remove_dividable(vector<uint32_t>& arr,uint32_t divisor)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        if(arr[i] % divisor == 0)
        {
            arr.erase(arr.begin()+i);
            if(i) i--;
        }
    }
}

void fill_from_keyboard(vector<uint32_t>& v,size_t count)
{
    while(count)
    {
        uint32_t element = read<uint32_t>(all);
        v.push_back(element);
        count--;
    }
}

int main()
{
    start();
    char user_answer;
    vector<uint32_t> arr = vector<uint32_t>();
    cout << "Y ���� ������ ������� �� input.txt\n";
    user_answer = read<char>(all);
    if (tolower(user_answer) == 'y')
    {
        ifstream file("input.txt");
        uint32_t datam;
        while (!file.eof())
        {
            file >> datam;
            arr.push_back(datam);
        }
    }else
    {
        size_t count = read<size_t>(natural_non_zero);
        fill_from_keyboard(arr,count);
    }
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
            cout << "{";
            for(auto a : arr) cout << a << " ";
            cout << "}" << endl;
            break;
        case '2':
        {
            cout << "������� ��� ���������." << endl;
            uint32_t element = read<uint32_t>(all);
            cout << "Y ���� ��������� ����� ����� ��������, ����� ����� ����������� ������� ��������." << endl;
            char opinion = read<char>(all);
            if (tolower(opinion) == 'y')
            {
                insert_after_fibonacci(arr,element);
            }   
            else
            {
                insert_after_min_full_square(arr,element);
            }
        }
        break;
        case '3':
        {
            cout << "������� ������� ���� �������." << endl;
            uint32_t a = read<uint32_t>(all);
            remove_dividable(arr,a);
        }
        break;
        case '0':
            cout << "exit" << endl;
            return 0;
            break;
        }
    } while (user_answer != '0');
}