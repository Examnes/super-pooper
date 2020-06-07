//#define _WIN32_WINNT
#include <cstring>
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include "windows.h"
#include <wincon.h>
#include <locale>

using namespace std;

typedef wstring txt_arr;

txt_arr from_file(string filename)
{
    wifstream file(filename);
    txt_arr text((istreambuf_iterator<wchar_t>(file)),istreambuf_iterator<wchar_t>());
    return text;
}

int count_words(txt_arr text)
{
    int ptr = 0;
    int count = 0;
    while (ptr < text.size())
    {
        if (isblank(text[ptr]))
        {
            while (isblank(text[ptr]) && ptr < text.size())
                ptr++;
        }
        else
        {
            count++;
            while (!isblank(text[ptr]) && ptr < text.size())
                ptr++;
        }
    }
    return count;
}

int main()
{
    system("chcp 65001");
    txt_arr txt = from_file("InW.dat");
    int count = count_words(txt);
    cout << "Количество слов: " << count << endl;
    wprintf(txt.c_str());
    int ptr = 0;
    while (count && txt[ptr])
    {
        cin.get();
        while (isblank(txt[ptr]) && txt[ptr])
            ptr++;
        system("cls");
        wprintf(L"%.*s", ptr, txt.c_str());
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hOutput, 12);
        while (!isblank(txt[ptr]) && txt[ptr])
        {
            putc(txt.data()[ptr++], stdout);
        }
        SetConsoleTextAttribute(hOutput, 15);
        wprintf(L"%s", txt.c_str() + ptr);
    }

    return 0;
}
