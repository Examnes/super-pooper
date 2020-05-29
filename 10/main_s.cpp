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

date *from_file(string filename, size_t &sz)
{
    ifstream file = ifstream(filename);
    string line;
    date *d = new date[100];
    sz = 100;
    size_t used = 0;
    while (getline(file, line))
    {
        stringstream parse = stringstream(line);
        date element;
        parse >> element.day;
        parse >> element.month;
        parse >> element.year;
        d[used++] = element;
        if (used == sz)
        {
            date *temp = new date[sz + 100];
            copy(d, d + sz, temp);
            delete[] d;
            d = temp;
            sz = sz + 100;
        }
    }
    date *temp = new date[used];
    copy(d, d + used, temp);
    delete[] d;
    sz = used;
    return temp;
}

void to_file(string filename, date *d, size_t sz)
{
    ofstream file = ofstream(filename, ios::binary);
    file.write((char *)d, sizeof(date) * sz);
}

void to_txt(string filename, date *d, size_t sz)
{
    ofstream file = ofstream(filename);
    for (int i = 0; i < sz; i++)
    {
        date a = d[i];
        file << a.day << " " << a.month << " " << a.year << endl;
    }
}

date *from_binnary(string filename, size_t &sz)
{
    ifstream file = ifstream(filename, ios::binary | ios::ate);
    sz = file.tellg();
    file.seekg(0);
    date *d = (date *)malloc(sz);
    file.read((char *)d, sz);
    sz = sz / sizeof(date);
    return d;
}

date *search_in_bin(string filename, string query, size_t &count)
{
    size_t sz;
    date *d = from_binnary(filename, sz);
    date *match = new date[sz];
    count = 0;
    copy_if(d, d + sz, match, [&](date v) {
        if (v.month == query || v.day == atoi(query.c_str()))
        {
            count++;
            return true;
        }
        return false;
    });
    delete[] d;
    date *temp = new date[count];
    copy(match, match + count, temp);
    delete match;
    return temp;
}

date *search_in_txt(string filename, string query, size_t &count)
{
    size_t sz;
    date *d = from_file(filename, sz);
    date *match = new date[sz];
    count = 0;
    copy_if(d, d + sz, match, [&](date v) {
        if (v.month == query || v.day == atoi(query.c_str()))
        {
            count++;
            return true;
        }
        return false;
    });
    delete[] d;
    date *temp = new date[count];
    copy(match, match + count, temp);
    delete match;
    return temp;
}

void sort_by_year(date *d, size_t sz)
{
    sort(d, d + sz, [](const date &lhs, const date &rhs) {
        return lhs.year < rhs.year;
    });
}

void print(date *d, size_t sz)
{
    cout << "Записи: " << endl;
    for (int i = 0; i < sz; i++)
    {
        date a = d[i];
        cout << i << ". " << a.day << " " << a.month << " " << a.year << endl;
    }
}

int main()
{
    system("chcp 1251");

    size_t sz;
    date *d = from_file("In.txt", sz);
    to_file("Out.bin", d, sz);

    size_t bin_sz;
    date *bin = from_binnary("Out.bin", bin_sz);
    print(bin, bin_sz);

    string query;
    cout << "Введите запрос: ";
    cin >> query;

    size_t search_sz;
    date *search = search_in_txt("In.txt", query, search_sz);
    to_file("Search.bin", search, search_sz);

    cout << "Введите запрос: ";
    cin >> query;

    size_t search_txt_sz;
    date *search_txt = search_in_txt("In.txt", query, search_txt_sz);
    to_txt("Search.txt", search_txt, search_txt_sz);

    sort_by_year(search_txt, search_txt_sz);
    to_txt("Out.txt", search_txt, search_txt_sz);

    delete[] d;
    delete[] bin;
    delete[] search;
    delete[] search_txt;
}