#include <iostream>
#include <limits>
#include <cmath>
#include <functional>
#include <iomanip>
using namespace std;

template<typename T>
T read(bool(*predicate)(T,T),T arg = 0)
{
    T x = 0;
    cin >> x;
    while((cin.fail())|| !predicate(x,arg))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> x;
    }
    return x;
}

template<typename T>
bool all(T a,T arg)
{
  return true;
}

template<typename T>
bool notNull(T a,T arg)
{
  return abs(a) > numeric_limits<float>::epsilon()*100;
}

template<typename T>
bool positive(T a,T arg)
{
  return a > 0;
}

template<typename T>
bool tillsTheEnd(T a,T arg)
{
  return abs(a) > numeric_limits<float>::epsilon()*100 && a > arg;
}

int fact(int N)
{
    if (N == 0) 
        return 1;
    else // �� ���� ��������� �������
        return N * fact(N - 1); // ������ ��������.
}

float f(float x, int n)
{
    float nom = x;
    for(int i = 0;i < 2 * n;i++) nom = nom * x;
    return (n % 2 == 1 ? -1 : 1) * nom / fact(2 * n + 1);
}

float CalcFunc(float x,float eps)
{
    float summ = 0;
    int n = 0;
    for(float arg = f(x,n); abs(arg) > eps; arg = f(x,n))
    {
        summ += arg;
        n++;
    }
    return summ;
}

float CalcFunc(float x, int n)
{
    float summ = 0;
    for(int i = 0; i < n; i++) summ += f(x,i);
    return summ;
}

int main(int, char**) 
{
    float a,b,e;
    int n;
    cout << "Введите a" << endl;
    a = read<float>(&all);
    cout << "Введите b" << endl;
    b = read<float>(&tillsTheEnd,a);
    cout << "Введите e" << endl;
    e = read<float>(&notNull);
    cout << "Введите N" << endl;
    n = read<int>(&positive);

    float h = (b-a)/10;
    cout << fixed << setprecision(5);
    for(float x = a; x < b; x += h)
    {
        float Sn,Se,S;
        Sn = CalcFunc(x,n);
        Se = CalcFunc(x,e);
        S = sin(x);
        cout << "x = " << x << " Sn = " << Sn << " Se = " << Se << " S = " << S << endl;
    }
}