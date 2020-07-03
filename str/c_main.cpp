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

int count_substr(const char *str, const char *substr)
{
    int count = 0;
    const char *tmp = str;
    while (tmp = strstr(tmp, substr))
    {
        count++;
        tmp++;
    }
    return count;
}

void replace(char *&str, const char *substr, const char *substitute)
{
    int diff = strlen(substitute) - strlen(substr);
    int sz = strlen(str) + diff * count_substr(str, substr);
    char *result = new char[sz + 1];
    ptrdiff_t str_ptr = 0;
    ptrdiff_t res_ptr = 0;
    char *sub_ptr;
    while (sub_ptr = strstr(str + str_ptr, substr))
    {
        copy(str + str_ptr, sub_ptr, result + res_ptr);
        res_ptr += (sub_ptr - (str + str_ptr));
        str_ptr += (sub_ptr - (str + str_ptr));
        
        strcpy(result + res_ptr, substitute);
        str_ptr += strlen(substr);
        res_ptr += strlen(substitute);
    } 
    strcpy(result + res_ptr, str + str_ptr);
    result[sz] = 0;
    delete str;
    str = result;
}

void exclude_braces(char*& str)
{
    char* res = new char[strlen(str)];
    memset(res,0,strlen(str));

    ptrdiff_t res_ptr = 0;
    ptrdiff_t str_ptr = 0;
    while (str[str_ptr])
    {
        if(str[str_ptr] == '\"')
        {
            str_ptr++;
            while (str[str_ptr] != '\"')
            {
                str_ptr++;
            }
            str_ptr++;
        }
        res[res_ptr++] = str[str_ptr++];
    }
    delete str;
    str = res;
}

void print_ids(char*& str)
{
    ofstream out("output.txt");
    exclude_braces(str);
    const array<string,108> keyword = {
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
        "\'9\'"
        };

    map<string, int> counts;
    char *token = strtok(str, " :-,.{}][></?!;%&*=+|~()\n\r");
    while (token != NULL)
    {
        if (!isdigit(token[0]) && !count(keyword.begin(),keyword.end(),string(token)))
        {
            counts[token]++;
        }
        token = strtok(NULL, " :-,.{}][></?!;%&*=+|~()\n\r");
    }

    for (const auto &kv : counts)
    {
        out << kv.first << " = " << kv.second << endl;
    }
}

int main()
{
    system("chcp 1251");

    ifstream file("input.txt",ios::ate);
    int sz = file.tellg();
    file.seekg(0);
    char* str = new char[sz];
    file.read(str,sz);
    string str1,str2;
    cout << "¬ведите что замен€ть" << endl;
    cin >> str1;
    cout << "¬ведите на что замен€ть" << endl;
    cin >> str2;
    replace(str,str1.c_str(),str2.c_str());
    cout << str << endl;
    ifstream code("main.cpp",ios::ate);
    int code_sz = code.tellg();
    char* code_str = new char[code_sz];
    code.seekg(0);
    code.read(code_str,code_sz);
    print_ids(code_str);
    system("pause");
    return 0;
}