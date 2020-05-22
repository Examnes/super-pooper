#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

float delta_x = 0.2f;
float delta_y = 0.2f;
float x_begin = -1.0f;
float x_end = 1.0f;
float y_begin = -1.0f;
float y_end = 1.0f;


float z(float x,float y)
{
    return log10(4-x*x-y*y);
}

void tab(ostream& stream)
{
    float delta_max = 0;
    float delta_min = 0;
    float max_begin = 0;
    float max_end = 0;
    float min_begin = 0;
    float min_end = 0;


    if((x_end - x_begin) / delta_x > (y_end - y_begin) / delta_y)
    {
        stream << "   x >\t";
        for(float x = x_begin;x < x_end;x += delta_x) stream << x << "\t";
        stream << endl << "x v" << endl;
        delta_max = delta_x;
        delta_min = delta_y;
        max_begin = x_begin;
        max_end = x_end;
        min_begin = y_begin;
        min_end = y_end;
    }
    else
    {
        stream << "   y >\t";
        for(float y = y_begin;y < y_end;y += delta_y) stream << y << "\t";
        stream << endl << "x v" << endl;
        delta_max = delta_y;
        delta_min = delta_x;
        max_begin = y_begin;
        max_end = y_end;
        min_begin = x_begin;
        min_end = x_end;
    }

    for(float y = min_begin;y < min_end;y += delta_min)
    {
        stream << y << "\t";
        for(float x = max_begin;x < max_end;x += delta_max) if(4-x*x-y*y > numeric_limits<float>::epsilon()){stream << z(x,y) << "\t";} else { stream << "*\t";}
        stream << endl;
    }
}

int main(int, char**) 
{
    int choise;
    cout << setprecision(3) << fixed << "Выводить в:" << endl
    << "1.Консоль" << endl
    << "2.Файл" << endl;

    cin >> choise;
    while( (cin.fail()) || (choise < 1) || (choise > 2) )
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> choise;
    }

    cout << "Введите начало отрезка по X" << endl;
    cin >> x_begin;
    while( (cin.fail()))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> x_begin;
    }

    cout << "Введите начало отрезка по Y" << endl;
    cin >> y_begin;
    while( (cin.fail()))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> y_begin;
    }

    cout << "Введите конец отрезка по X" << endl;
    cin >> x_end;
    while( (cin.fail()) || x_end < x_begin || x_end-x_begin < numeric_limits<float>::epsilon()*100)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> x_end;
    }

    cout << "Введите конец отрезка по Y" << endl;
    cin >> y_end;
    while( (cin.fail()) || y_end < y_begin || y_end-y_begin < numeric_limits<float>::epsilon()*100)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> y_end;
    }

    cout << "Введите шаг по X" << endl;
    cin >> delta_x;
    while( (cin.fail()) || abs(delta_x) > (x_end-x_begin) || delta_x < numeric_limits<float>::epsilon()*100)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> delta_x;
    }

    cout << "Введите шаг по Y" << endl;
    cin >> delta_y;
    while( (cin.fail()) || abs(delta_y) > (y_end-y_begin) || delta_y < numeric_limits<float>::epsilon()*100)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> delta_y;
    }

    switch (choise)
    {
    case 1:
        tab(cout);
        break;
    case 2:
        cout << "Введите название файла" << endl;
        char fname[100];
        cin >> fname;

        while(cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            cin >> fname;
        }

        ofstream fout(fname);
        fout << setprecision(2) << fixed;
        tab(fout);
        fout.close();
        break;
    }
    
    return 0;
}
