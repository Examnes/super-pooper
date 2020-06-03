#include <cstring>
#include <string>
#include <array>
#include <fstream>

using namespace std;

array<char, 1200> from_file(string filename)
{
    ifstream file;
    file.open(filename, ios::ate);
    array<char, 1200> text;
    size_t sz = file.tellg();
    file.seekg(0);
    file.read((char *)text.data(), sz);
    return text;
}


