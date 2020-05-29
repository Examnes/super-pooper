#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
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

struct date
{
    int day;
    char month[8];
    int year;
}; 

vector<date> from_file(string filename)
{
    ifstream file = ifstream(filename);
    string line;
    vector<date> v;
    while(getline(file,line))
    {
        stringstream parse = stringstream(line);
        date element;
        parse >> element.day;
        parse >> element.month;
        parse >> element.year;
        v.push_back(element);
    }
    return v;
}

void to_file(string filename,vector<date> v)
{
    ofstream file = ofstream(filename,ios::binary);
    file.write((char*)v.data(),sizeof(date) * v.size());
}

void to_txt(string filename,vector<date> v)
{
    ofstream file = ofstream(filename);
    for(auto a : v)
    {
        file << a.day << " " << a.month << " " << a.year << endl;
    }
}

vector<date> from_binnary(string filename)
{
    ifstream file = ifstream(filename,ios::binary | ios::ate);
    size_t sz = file.tellg();
    file.seekg(0);
    vector<date> v(sz / sizeof(date));
    file.read((char*)v.data(),sz);
    return v;
}

vector<date> search_in_bin(string filename,string query)
{
    vector<date> v = from_binnary(filename);
    vector<date> match;
    copy_if(v.begin(),v.end(),back_inserter(match),[&](date v) 
    {
        return v.month == query || v.day == atoi(query.c_str());
    });
    match.shrink_to_fit();
    return match;
}

vector<date> search_in_txt(string filename,string query)
{
    vector<date> v = from_file(filename);
    vector<date> match;
    copy_if(v.begin(),v.end(),back_inserter(match),[&](date v) 
    {
        return v.month == query || v.day == atoi(query.c_str());
    });
    return match;
}

void sort_by_year(vector<date>& v)
{
    sort( v.begin( ), v.end( ), [ ]( const date& lhs, const date& rhs )
    {
    return lhs.year < rhs.year;
    });
}

void print(vector<date> v)
{
    cout << "Записи: " << endl;
    int i = 0;
    for(auto a : v)
    {
        i++;
        cout << i << ". " << a.day << " " << a.month << " " << a.year << endl;
    }
}

int main()
{
    system("chcp 1251");
    vector<date> v = from_file("In.txt");
    to_file("Out.bin",v);
    v = from_binnary("Out.bin");
    print(v);
    string query;
    cout << "Введите запрос: ";
    cin >> query;
    vector<date> m = search_in_bin("Out.bin",query);
    to_txt("Search.txt",m);
    m = search_in_txt("In.txt",query);
    to_file("Search.bin",m);
    vector<date> elements = from_file("Search.txt");
    sort_by_year(elements);
    print(elements);
    system("pause");
}