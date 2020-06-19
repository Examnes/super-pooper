#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <conio.h>

using namespace std;

set<int, less<int>> to_set(int number)
{
    set<int, less<int>> s;
    while (number)
    {
        s.insert(number % 10);
        number /= 10;
    }
    return s;
}

int get_digit(int num, int i)
{
    int mul = 1;
    while (i)
    {
        mul *= 10;
        i--;
    }
    return (num / mul) % 10;
}

const string products[9] =
    {
        "Яблоки",
        "Груши",
        "Колбаса",
        "Молоко",
        "Огурцы",
        "Капуста",
        "Масло",
        "Блинчики",
        "Яйца",
};


void first()
{
    set<int, less<int>> shop[3];
        for (int i = 0; i < 3; i++)
        {
            cout << "Доступные товары:" << endl;
            for (auto a : products)
            {
                cout << a << endl;
            }
            cout << "Добавьте товары в " << i + 1 << " магазин (номера товаров из списка, 0 - чтобы закончить)" << endl;
            char choice = getch();
            while (choice - '0')
            {
                if (isdigit(choice))
                    shop[i].insert(choice - '1');
                cout << choice << endl;
                choice = getch();
            }
        }
        cout << endl;

        cout << "В 1 магазине:" << endl;
        for (auto a : shop[0])
        {
            cout << products[a] << endl;
        }

        cout << "В 2 магазине:" << endl;
        for (auto a : shop[1])
        {
            cout << products[a] << endl;
        }

        cout << "В 3 магазине:" << endl;
        for (auto a : shop[2])
        {
            cout << products[a] << endl;
        }

        cout << "Товары, которые есть во всех магазинах:" << endl;
        set<int, less<int>> all;
        set<int, less<int>> one_two;
        set_intersection(shop[0].begin(), shop[0].end(), shop[1].begin(), shop[1].end(), inserter(one_two, one_two.begin()));
        set_intersection(one_two.begin(), one_two.end(), shop[2].begin(), shop[2].end(), inserter(all, all.begin()));
        if (!all.empty())
            for (auto a : all)
            {
                cout << products[a] << endl;
            }
        cout << endl;
        set<int, less<int>> uniq_shop[3];
        set_difference(shop[0].begin(), shop[0].end(), all.begin(), all.end(), inserter(uniq_shop[0], uniq_shop[0].begin()));
        set_difference(shop[1].begin(), shop[1].end(), all.begin(), all.end(), inserter(uniq_shop[1], uniq_shop[1].begin()));
        set_difference(shop[2].begin(), shop[2].end(), all.begin(), all.end(), inserter(uniq_shop[2], uniq_shop[2].begin()));

        set<int, less<int>> two;

        set_intersection(uniq_shop[0].begin(), uniq_shop[0].end(), uniq_shop[1].begin(), uniq_shop[1].end(), inserter(two, two.begin()));
        set_intersection(uniq_shop[1].begin(), uniq_shop[1].end(), uniq_shop[2].begin(), uniq_shop[2].end(), inserter(two, two.begin()));
        set_intersection(uniq_shop[0].begin(), uniq_shop[0].end(), uniq_shop[2].begin(), uniq_shop[2].end(), inserter(two, two.begin()));

        cout << "Товары, которые есть только в двух магазинах:" << endl;
        if (!two.empty())
            for (auto a : two)
            {
                cout << products[a] << endl;
            }
        cout << endl;

        set<int, less<int>> once;

        set_difference(uniq_shop[0].begin(), uniq_shop[0].end(), two.begin(), two.end(), inserter(once, once.begin()));
        set_difference(uniq_shop[1].begin(), uniq_shop[1].end(), two.begin(), two.end(), inserter(once, once.begin()));
        set_difference(uniq_shop[2].begin(), uniq_shop[2].end(), two.begin(), two.end(), inserter(once, once.begin()));

        cout << "Товары, которые есть только в одном магазине:" << endl;
        if (!once.empty())
            for (auto a : once)
            {
                cout << products[a] << endl;
            }
        cout << endl;
}

void second()
{
    ifstream file("In.dat");
    set<char, less<char>> consonants;
    set<char, less<char>> vowels;
    set<char, less<char>> vowels_ideal{(char)'у', (char)'е', (char)'ы', (char)'а', (char)'о', (char)'э', (char)'я', (char)'и', (char)'ю'};
    while (file.peek() != EOF)
    {
        string word;
        file >> word;
        const char *c_conson = "цкнгшщзхфвпрлджчмтб";

        const char *c_wowels = "уеыаоэяию";

        for (auto c : word)
        {
            if (count(c_conson, c_conson + 19, c) != 0)
                if (count(word.begin(), word.end(), c) >= 2)
                    consonants.insert(c);

            if (count(c_wowels, c_wowels + 9, c) != 0)
                if (vowels_ideal.find(c) != vowels_ideal.end())
                {
                    vowels_ideal.erase(c);
                    vowels.insert(c);
                }
                else
                {
                    vowels.erase(c);
                }
        }
    }

    cout << "Согласные буквы, которые встреяаютсяя в слове 2 раза:" << endl;
    for (auto a : consonants)
        cout << a << endl;
    cout << "Гласные буквы, встречающиеся только в одном слове:" << endl;
    for (auto a : vowels)
        cout << a << endl;

}

void thrid()
{
    cout << "АСТРА + ИРИС = ЦВЕТЫ" << endl;
    for (int i = 1000; i < 9999; i++)
    {
        int t,a,r,s;
        t = get_digit(i,1);
        a = get_digit(i,3);
        r = i % 10;
        s = get_digit(i,2);
        int astra = i * 10 + a;
        set<int, less<int>> astra_num = to_set(astra);
        if (astra_num.size() == 4)
            for (int j = 0; j < 9; j++)
            {
                if (astra_num.find(j) == astra_num.end())
                {
                    int iris = (j * 1000 + r * 100 + j * 10 + s);
                    int cvety = astra + iris;
                    set<int, less<int>> cvety_num = to_set(cvety);
                    set<int, less<int>> iris_num = to_set(iris);

                    set<int, less<int>> uni;
                    set_union(astra_num.begin(),astra_num.end(),iris_num.begin(),iris_num.end(),inserter(uni,uni.begin()));

                    set<int, less<int>> cv_itersect;
                    set_intersection(cvety_num.begin(),cvety_num.end(),uni.begin(),uni.end(),inserter(cv_itersect,cv_itersect.begin()));
                    
                    if (get_digit(cvety, 1) == t && cvety < 100000 && cvety_num.size() == 5 && cv_itersect.size() == 1)
                    {
                        cout << astra << " + " << iris << " = " << cvety << endl;
                    }
                }
            }
        
    }
}

int do_menue()
{
    cout << "Введите номер задания:\n1.Найти какие товары продаются в каких магазинах\n2.Найти гласные и согласные буквы\n3.Найти решение ребуса";
    int choise = 0;
    while(choise > '3' || choise < '1')
    {
        choise = getch();
        cout << choise << endl;
    }
    return choise - '0';
}

int main()
{
    system("chcp 1251");
    while (true)
    {
        int option = do_menue();
        switch (option)
        {
        case 1:
            first();
            break;
        case 2:
            second();
            break;
        case 3:
            thrid();
            break;
        default:
            break;
        }
    }
    system("pause");
    return 0;
}