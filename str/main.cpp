#define __SSP_FORTIFY_LEVEL 1
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <array>

using namespace std;

int count_substr(string str, string substr)
{
    int count = 0; 
    size_t pos = str.find(substr);
    while (pos != std::string::npos)
    {
        count++;
        pos = str.find(substr, pos + substr.size());
    }
    return count;
}

void replace(std::string &str, std::string substr, std::string substitute)
{
    size_t pos = str.find(substr);
    while (pos != std::string::npos)
    {
        str.replace(pos, substr.size(), substitute);
        pos = str.find(substr, pos + substitute.size());
    }
}

string exclude_braces(string str)
{
    string res;
    size_t pos = 0;
    std::string token;
    int i = 0;
    while ((pos = str.find('\"')) != std::string::npos)
    {
        token = str.substr(0, pos);
        if(i % 2 == 0) res += token;
        str.erase(0, pos + 1);
        i++;
    }
    res += str;
    return res;
}

void print_ids(string str)
{
    ofstream out("output.txt");
    str = exclude_braces(str);
    const array<string, 108> keyword = {
        "int",
        "alignas",
        "alignof",
        "and",
        "and_eq",
        "asm",
        "atomic_cancel",
        "atomic_commit",
        "atomic_noexcept",
        "auto",
        "bitand",
        "bitor",
        "bool",
        "break",
        "case",
        "catch",
        "char",
        "char8_t",
        "char16_t",
        "char32_t",
        "class",
        "compl",
        "concept",
        "const",
        "consteval",
        "constexpr",
        "constinit",
        "const_cast",
        "continue",
        "co_await",
        "co_return",
        "co_yield",
        "decltype",
        "default",
        "delete",
        "do",
        "double",
        "dynamic_cast",
        "else",
        "enum",
        "explicit",
        "export",
        "extern",
        "false",
        "float",
        "for",
        "friend",
        "goto",
        "if",
        "inline",
        "int",
        "long",
        "mutable",
        "namespace",
        "new",
        "noexcept",
        "not",
        "not_eq",
        "nullptr",
        "operator",
        "or",
        "or_eq",
        "private",
        "protected",
        "public",
        "reflexpr",
        "register",
        "reinterpret_cast",
        "requires",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "static_assert",
        "static_cast",
        "struct",
        "switch",
        "synchronized",
        "template",
        "this",
        "thread_local",
        "throw",
        "true",
        "try",
        "typedef",
        "typeid",
        "typename",
        "union",
        "unsigned",
        "using",
        "virtual",
        "void",
        "volatile",
        "wchar_t",
        "while",
        "xor",
        "xor_eq",
        "\'0\'",
        "\'1\'",
        "\'2\'",
        "\'3\'",
        "\'4\'",
        "\'5\'",
        "\'6\'",
        "\'7\'",
        "\'8\'",
        "\'9\'"};
    map<string, int> counts;
    string delimiter = " :-,.{}][></?!;%&*=+|~()\n\r";

    size_t beg, pos = 0;
    while ((beg = str.find_first_not_of(delimiter, pos)) != std::string::npos)
    {
        pos = str.find_first_of(delimiter, beg + 1);
        string token = str.substr(beg, pos - beg);
        if (!isdigit(token[0]) && !count(keyword.begin(), keyword.end(), string(token)))
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
    system("chcp 1251");

    ifstream t("input.txt",ios::ate);
    std::string str; 
    str.reserve(t.tellg());
    t.seekg(0);
    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

    string str1, str2;
    cout << "¬ведите что замен€ть" << endl;
    cin >> str1;
    cout << "¬ведите на что замен€ть" << endl;
    cin >> str2;
    replace(str, str1, str2);
    cout << str << endl;
    ifstream code("main.cpp",ios::ate);
    std::string code_str; 
    code_str.reserve(code.tellg());
    code.seekg(0);
    code_str.assign((std::istreambuf_iterator<char>(code)),
                std::istreambuf_iterator<char>());
    print_ids(code_str);
    system("pause");
    return 0;
}