#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <string>
#include <cstring>
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

struct fract
{
    long nom;
    long denom;
};

template<typename T>
bool suitable(T a,T arg)
{
    return a > 0 && a < arg;
}

long GCD(long a,long b)
{
    while (a && b) 
    {
        if (a>b) 
        {
            a = a % b;
        }
        else b = b % a;
    }
    return a + b;
}

void truncate(long& a, long& b)
{
    long gcd = GCD(a,b);
    a = a / gcd;
    b = b / gcd;
}

void truncate(fract& a)
{
    truncate(a.nom,a.denom);
}

string fraction_to_string(long a,long b)
{
    char buf[20];
    string fraction = string();
    fraction += _ltoa(a,buf,10);
    fraction += "\n";
    for(unsigned char i = 0;i<strlen(buf);i++) fraction += "-";
    fraction += "\n";
    fraction += _ltoa(b,buf,10);
    return fraction;
}

string fraction_to_string(fract& a)
{
    return fraction_to_string(a.nom,a.denom);
}

void summ(long& a,long& b,long c,long d)
{
    if(b != d)
    {
        a = a * d;
        c = c * b;
        b = b * d;
    }
    a = a + c;
}

fract summ(fract a,fract b)
{
    if(a.denom != b.denom)
    {
        a.nom = a.nom * b.denom;
        b.nom = b.nom * a.denom;
        a.denom = a.denom * b.denom;
    }
    a.nom = a.nom + b.nom;
    return a;
}

void mul(fract& a,long n)
{
    a.nom *= n;
}

void prlong_n_elem(long n)
{
    long a_nom = 1;
    long a_denom = 1;
    for(long i = 2;i < n;i++)
    {
        a_nom *= i;
        summ(a_nom,a_denom,-1,i);
        cout << "N = " << i << " An: \n\n" << fraction_to_string(a_nom,a_denom) << endl << endl;
    }
    truncate(a_nom,a_denom);
    cout << "Результат: \n\n" << fraction_to_string(a_nom,a_denom) << endl;
}

void prlong_n_elem_fr(long n)
{
    fract a;
    a.nom = 1;
    a.denom = 1;
    for(long i = 2;i < n;i++)
    {
        mul(a,i);
        a = summ(a,{-1,i});
        cout << "N = " << i << " An: \n\n" << fraction_to_string(a) << endl << endl;
    }
    truncate(a);
    cout << "Результат: \n\n" << fraction_to_string(a) << endl;
}

int main(int argc,char** argv)
{
    
    cout << "Введите N < 10" << endl;
    long n = read<long>(&suitable,10);
    cout << "Без использования структур" << endl;
    prlong_n_elem(n);
    cout << endl;
    cout << "C использованием структур" << endl;
    prlong_n_elem_fr(n);
    return 0;
}
