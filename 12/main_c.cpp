//#define _WIN32_WINNT
#include <cstring>
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include "windows.h"
#include <wincon.h>

using namespace std;

typedef array<char, 1201> txt_arr;

txt_arr from_file(string filename)
{
    ifstream file;
    file.open(filename, ios::ate);
    txt_arr text;
    size_t sz = file.tellg();
    file.seekg(0);
    file.read((char *)text.data(), sz);
    text[sz] = 0;
    return text;
}

int count_words(txt_arr text)
{
    int ptr = 0;
    int count = 0;
    while (text[ptr])
    {
        if (isblank(text[ptr]))
        {
            while (isblank(text[ptr]) && text[ptr])
                ptr++;
        }
        else
        {
            count++;
            while (!isblank(text[ptr]))
                ptr++;
        }
    }
    return count;
}

int main()
{
    system("chcp 1251");
    txt_arr txt = from_file("In.dat");
    int count = count_words(txt);
    cout << "Количество слов: " << count << endl;
    cout << txt.data();
    int ptr = 0;
    while (count && txt[ptr])
    {
        cin.get();
        while (isblank(txt[ptr]) && txt[ptr])
            ptr++;
        system("cls");
        printf("%.*s", ptr, txt.data());
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hOutput, 12);
        while (!isblank(txt[ptr]) && txt[ptr])
        {
            putc(txt.data()[ptr++], stdout);
        }
        SetConsoleTextAttribute(hOutput, 15);
        printf("%s", txt.data() + ptr);
    }

    return 0;
}
