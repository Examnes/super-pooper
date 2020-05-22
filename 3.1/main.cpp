#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
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
bool digit(T a,T arg)
{
  return a>=0&&a<=9;
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

bool contains(int N,int K)
{
    while(N > 0)
    {
        int r = N % 10;
        if(r == K) return true;
        N = N / 10;
    }
    return false;
}

int main(int, char**) 
{
    cout << "¬ведите число положительное не слишком большое." << endl;
    unsigned int N = read<int>(&positive);
    cout << "¬ведите цифру." << endl;
    int M = read<int>(&digit);
    cout << "¬ведите цифру." << endl;
    int K = read<int>(&digit);

    if (contains(N,K)) cout << "N содержит " << K << endl;
    if (contains(N,M)) cout << "N содержит " << M << endl;

    return 0;
}
