#include <iostream>
#include <algorithm>
#include <string>
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
bool all(T a, T arg)
{
    return true;
}

template <typename T>
bool notNull(T a, T arg)
{
    return abs(a) > numeric_limits<float>::epsilon() * 100;
}

template <typename T>
bool positive(T a, T arg)
{
    return a > 0;
}

string sum_big(string first,string second)
{
    if(second.size() > first.size()) swap(first,second);
    string res;
    if(first[0]!='-')
    {
        if(second[0]!='-')
        {
            reverse(first.begin(),first.end());
            reverse(second.begin(),second.end());
            int carry = 0;
            for(int i = 0;i < second.size();i++)
            {
                int num = first[i] + second[i] - 48 + carry;
                carry = (num - 48) >= 10;

                if(carry)
                {
                    num -= 10;
                }
                res += num;
            }
            for(int i = second.size();i < first.size();i++)
            {
                int num = first[i] + carry;
                carry = num % 58;
                if(carry)
                {
                    num -= 10;
                }
                res += num;
            }
            if(carry) res += "1"; 
            return res;
        }else
        {
            
        }
    }else
    {
        if(second[0]!='-')
        {

        }else
        {
            return "-" + sum_big(first.substr(1,first.size()),first.substr(1,first.size()));
        }
    }
    return "0";
}

int main()
{
    system("chcp 65001");
    string first_s;
    string second_s;
    cout << "Введите первое число" << endl;
    cin >> first_s;
    cout << "Введите второе число" << endl;
    cin >> second_s;
    int median = 0;
    string res = sum_big(first_s,second_s);
    for(auto a : res)
        median += a - 48;
    median /= (float)res.size();
    cout << "Среднее арифметическе: " << median << endl;
    system("pause");
    return 0;
}
