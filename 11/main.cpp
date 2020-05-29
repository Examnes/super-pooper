#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <scanner.hh>
#include <cstring>
using namespace std;

template <typename T>
T read(bool (*predicate)(T, int), int arg = 0)
{
    T x;
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
bool answer(T a, int b)
{
    return a >= 0 && a <= 3;
}

template <typename T>
bool all(T a, int b)
{
    return true;
}

template <typename T>
bool greather(T a, int arg)
{
    return a > arg;
}

template <typename T>
bool lower(T a, T arg)
{
    return a < arg;
}

template <typename T>
bool shorter(T a,int arg)
{
    return a.size() < arg;
}


int main()
{
    system("chcp 65001");
    int choise;
    do
    {
        cout << "Введите номер операции:\n1.Вывести\n2.сортировать по\n3.Добавить\n0.Выйти" << endl;
        choise = read<int>(answer);
        switch (choise)
        {
        case 1:
            print("Scanners.bin");
            system("pause");
            break;
        case 2:
            {
            cout << "Введите Y если хотите отсортировать по стоимости или что-нибудь еще, чтобы отсортировать по градации серого" << endl;
            char grad = read<char>(all);
            sort_by("Scanners.bin",tolower(grad) == 'y' ? scanner_traits::price : scanner_traits::grey);
            system("pause");
            }
            break;
        case 3:
            {
                vector<scanner> v;
                char should_continue = 'n';
                do
                {
                    scanner s;
                    memset(&s,0,sizeof(scanner));
                    cout << "Введите название модели" << endl;
                    string model = read<string>(shorter,25);
                    memcpy(s.model,model.c_str(),model.size());
                    cout << "Введите цену" << endl;
                    s.price = read<int>(greather,0);
                    cout << "Введите длину" << endl;
                    s.x_size = read<double>(greather,0);
                    cout << "Введите ширину" << endl;
                    s.y_size = read<double>(greather,0);
                    cout << "Введите разрешение" << endl;
                    s.optr = read<int>(greather,0);
                    cout << "Введите число градаций серого" << endl;
                    s.grey = read<int>(greather,0);
                    v.push_back(s);
                    cout << "Введите Y если хотите внести еще одну запись, или что либо еще чтобы сохранить изменения в файле" << endl;
                    should_continue = read<char>(all);
                }while(tolower(should_continue) == 'y');
                append("Scanners.bin",v);
                system("pause");
            }
            break;
        default:
            break;
        }
        system("cls");
    } while (choise);
    
    return 0;
}