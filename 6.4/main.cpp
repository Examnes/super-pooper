#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include <array>
#include <assert.h>
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
    cout << "эта программа позволяет делать операции над связным списком. При операции добавления число будет добавлено после наименьшего из полных квадратов, если пользователь не пожелает добавить элемент после чисел фибоначчи или если в списке вовсе нет полных квадратов.\n";
    cout << "при операции удаления программа удалит все числа, кратные тому, что введет пользователь, а так же предложит удалить произвольный элемент.\n";
}

void insert_after_fibonacci(array<uint32_t,20>& arr,uint32_t element,size_t& sz)
{
    for(size_t i = 0;i < sz;i++)
    {
        if(isFibonacci(arr[i]))
        {
            for(size_t j = sz;j > i;j--)
            {
                arr[j] = arr[j-1];
            }
            arr[i] = element;
            sz++;
            i++;
        }
    }
}

void insert_after_min_full_square(array<uint32_t,20>& arr,uint32_t element,size_t& sz)
{
    assert(sz < 20);
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
        rotate(arr.rbegin()+index,arr.rbegin()+1+index,arr.rend());
        arr[index] = element;
        sz++;
    }
}

void remove_dividable(array<uint32_t,20>& arr,uint32_t divisor,size_t& sz)
{
    for (size_t i = 0; i < sz; i++)
    {
        if(arr[i] % divisor == 0)
        {
            rotate(arr.begin()+i,arr.begin()+1+i,arr.end());
            if(i) i--;
            sz--;
        }
    }
}

void fill_from_keyboard(array<uint32_t,20>& arr,size_t count)
{
    size_t ptr = 0;
    while(count)
    {
        uint32_t element = read<uint32_t>(all);
        arr[ptr++] = element;
        count--;
    }
}

int main()
{
start();
    char user_answer;
    array<uint32_t,20> arr;
    arr.fill(0);
    size_t sz = 0;
    cout << "Y если хотите считать из input.txt\n";
    user_answer = read<char>(all);
    if (tolower(user_answer) == 'y')
    {
        ifstream file("input.txt");
        uint32_t datam;
        size_t ptr = 0;
        while (!file.eof())
        {
            file >> datam;
            arr[ptr++] = datam;
        }
        sz = ptr;
    }else
    {
        size_t count = read<size_t>(natural_non_zero);
        fill_from_keyboard(arr,count);
        sz = count;
    }
    user_answer = 0;
    do
    {
        cout
            << "Операции:" << endl
            << "1.вывести" << endl
            << "2.добавить(1.1 1.2)" << endl
            << "3.удалить (2)" << endl
            << "0.выйти" << endl;

        char user_answer = read<char>(answer);
        switch (user_answer)
        {
        case '1':
            cout << "{";
            for(size_t i = 0;i<sz;i++)
            cout << arr[i] << " ";
            cout << "}" << endl;
            break;
        case '2':
        {
            cout << "введите что вставлять." << endl;
            uint32_t element = read<uint32_t>(all);
            cout << "Y если вставлять после чисел фибоначи, иначе после наибольшего полного квадрата." << endl;
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
            cout << "Введите кратное чему удалять." << endl;
            uint32_t a = read<uint32_t>(all);
            remove_dividable(arr,a,sz);
        }
        break;
        case '0':
            cout << "exit" << endl;
            return 0;
            break;
        }
    } while (user_answer != '0');
}