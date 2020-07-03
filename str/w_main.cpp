#define __SSP_FORTIFY_LEVEL 1
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <array>
#include <windows.h>



using namespace std;

int count_substr(wstring str, wstring substr)
{
    int count = 0; 
    size_t pos = str.find(substr);
    while (pos != wstring::npos)
    {
        count++;
        pos = str.find(substr, pos + substr.size());
    }
    return count;
}

void replace(std::wstring &str, std::wstring substr, std::wstring substitute)
{
    size_t pos = str.find(substr);
    while (pos != std::wstring::npos)
    {
        str.replace(pos, substr.size(), substitute);
        pos = str.find(substr, pos + substitute.size());
    }
}

wstring exclude_braces(wstring str)
{
    wstring res;
    size_t pos = 0;
    std::wstring token;
    int i = 0;
    while ((pos = str.find('\"')) != std::wstring::npos)
    {
        token = str.substr(0, pos);
        if(i % 2 == 0) res += token;
        str.erase(0, pos + 1);
        i++;
    }
    res += str;
    return res;
}

void print_ids(wstring str)
{
    wofstream out("output.txt");
    str = exclude_braces(str);
    const array<wstring, 108> keyword = {
        L"int",
        L"alignas",
        L"alignof",
        L"and",
        L"and_eq",
        L"asm",
        L"atomic_cancel",
        L"atomic_commit",
        L"atomic_noexcept",
        L"auto",
        L"bitand",
        L"bitor",
        L"bool",
        L"break",
        L"case",
        L"catch",
        L"char",
        L"char8_t",
        L"char16_t",
        L"char32_t",
        L"class",
        L"compl",
        L"concept",
        L"const",
        L"consteval",
        L"constexpr",
        L"constinit",
        L"const_cast",
        L"continue",
        L"co_await",
        L"co_return",
        L"co_yield",
        L"decltype",
        L"default",
        L"delete",
        L"do",
        L"double",
        L"dynamic_cast",
        L"else",
        L"enum",
        L"explicit",
        L"export",
        L"extern",
        L"false",
        L"float",
        L"for",
        L"friend",
        L"goto",
        L"if",
        L"inline",
        L"int",
        L"long",
        L"mutable",
        L"namespace",
        L"new",
        L"noexcept",
        L"not",
        L"not_eq",
        L"nullptr",
        L"operator",
        L"or",
        L"or_eq",
        L"private",
        L"protected",
        L"public",
        L"reflexpr",
        L"register",
        L"reinterpret_cast",
        L"requires",
        L"return",
        L"short",
        L"signed",
        L"sizeof",
        L"static",
        L"static_assert",
        L"static_cast",
        L"struct",
        L"switch",
        L"synchronized",
        L"template",
        L"this",
        L"thread_local",
        L"throw",
        L"true",
        L"try",
        L"typedef",
        L"typeid",
        L"typename",
        L"union",
        L"unsigned",
        L"using",
        L"virtual",
        L"void",
        L"volatile",
        L"wchar_t",
        L"while",
        L"xor",
        L"xor_eq",
        L"\'0\'",
        L"\'1\'",
        L"\'2\'",
        L"\'3\'",
        L"\'4\'",
        L"\'5\'",
        L"\'6\'",
        L"\'7\'",
        L"\'8\'",
        L"\'9\'"};
    map<wstring, int> counts;
    wstring delimiter = L" :-,.{}][></?!;%&*=+|~()\n\r";

    size_t beg, pos = 0;
    while ((beg = str.find_first_not_of(delimiter, pos)) != std::wstring::npos)
    {
        pos = str.find_first_of(delimiter, beg + 1);
        wstring token = str.substr(beg, pos - beg);
        if (!isdigit(token[0]) && !count(keyword.begin(), keyword.end(), wstring(token)))
        {
            counts[token]++;
        }
    }

    for (const auto &kv : counts)
    {
        out << kv.first << " = " << kv.second << endl;
    }
}

int main()
{
    const HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdIn == INVALID_HANDLE_VALUE)
        throw "что то не так с консолью";

    static const int kBufferLen = 200;
    wchar_t buffer[kBufferLen];
    DWORD numRead = 0;

    setlocale(LC_ALL, "");
    wifstream t("input.txt",ios::ate);
    std::wstring str; 
    str.reserve(t.tellg());
    t.seekg(0);
    str.assign((std::istreambuf_iterator<wchar_t>(t)),
                std::istreambuf_iterator<wchar_t>());
    wstring str1, str2;
    wcout << L"Введите что заменять\n";
    ReadConsoleW(hStdIn, buffer, kBufferLen, &numRead, nullptr);
    str1 = wstring(buffer,numRead - 2);
    wcout << L"Вы ввели - " << str1 << endl;
    wcout << L"Введите на что заменять\n";
    memset(buffer,0,400);
    ReadConsoleW(hStdIn, buffer, kBufferLen, &numRead, nullptr);
    str2 = wstring(buffer,numRead - 2);
    wcout << L"Вы ввели - " << str2 << endl;
    replace(str, str1, str2);
    wcout << str << endl;
    wifstream code("main.cpp",ios::ate);
    std::wstring code_str; 
    code_str.reserve(code.tellg());
    code.seekg(0);
    code_str.assign((std::istreambuf_iterator<wchar_t>(code)),
                std::istreambuf_iterator<wchar_t>());
    print_ids(code_str);
    system("pause");
    return 0;
}