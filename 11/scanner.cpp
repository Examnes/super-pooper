#include <scanner.hh>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

void append(std::string filename, std::vector<scanner> v)
{
    fstream file; file.open(filename, ios::binary | ios::ate | ios::in | ios::out);
    if(!file) 
    {
        file.open(filename, ios::binary | ios::out);
        short sz = v.size();
        file.write((char *)&sz, sizeof(short));
        file.write((char *)v.data(), sizeof(scanner) * v.size());
        return;
    }
    file.write((char *)v.data(), sizeof(scanner) * v.size());
    size_t sz = file.tellg();
    sz -= sizeof(short);
    sz /= sizeof(scanner);
    file.seekg(0);
    file.write((char *)&sz, sizeof(short));
}

void sort_by(std::string filename, scanner_traits tr)
{
    fstream file; file.open(filename, ios::binary | ios::in | ios::out);
    if(file)
    {
        short count;
        file.read((char *)&count, sizeof(short));
        vector<scanner> v(count);
        file.read((char *)v.data(), count * sizeof(scanner));
        if (tr == scanner_traits::grey)
        {
            sort(v.begin(), v.end(), [](const scanner &a, const scanner &b) -> bool {
                return a.grey > b.grey;
            });
        }
        else
        {
            sort(v.begin(), v.end(), [](const scanner &a, const scanner &b) -> bool {
                return a.price > b.price;
            });
        }
        file.seekg(2);
        file.write((char *)v.data(), sizeof(scanner) * v.size());
    }
}

void print(std::string filename)
{
    fstream file = fstream(filename, ios::binary | ios::in | ios::out);
    if(file)
    {
        short count;
        file.read((char *)&count, sizeof(short));
        vector<scanner> v(count);
        file.read((char *)v.data(), count * sizeof(scanner));
        cout << "Записи:" << endl;
        for(auto a : v)
        {
            cout << a.model << " " << a.price << " " << a.x_size << "x" << a.y_size << " " << a.optr << " " << a.grey << endl;
        }
    }
}