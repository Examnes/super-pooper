#include "util.h"
#include <iostream>
#include <locale>
#include <chrono> 

using namespace std;
using namespace chrono;

int main()
{
    setlocale(LC_ALL, "Russian");

    saver();

    cout<<"Сейчас вам будет предложено ввести путь к файлу, содержащему точки."<<endl;
    cout<<"Введите путь к файлу."<<endl;
    string fname;
    cin>>fname;

    int error = 0;
    vector<point> points = fromFile(fname,error);
    if(error)
    {
        return error;
    }

    float max = 0.0f;
    size_t pointsOfMaxSquare[4];
    size_t sz = points.size();

    for(size_t i = 0;i<sz;i++)
    {
        for(size_t j = 0;j<sz;j++)
        {
            if (i == j) continue;
            for(size_t k = 0;k<sz;k++)
            {
                if ( j == k || i == k) continue;
                for(size_t l = 0;l<sz;l++)
                {
                    if ( j == k || l == j || i == l || i == k || l == k) continue;
                    float length = fromSquareOneSide(points[i],points[j],points[k],points[l]);
                    if(length>max)
                    {
                        pointsOfMaxSquare[0] = i;
                        pointsOfMaxSquare[1] = j;
                        pointsOfMaxSquare[2] = k;
                        pointsOfMaxSquare[3] = l;
                        max = length;
                    }
                }
            }
        }
    }

    if(max)
    {
        cout<<"Квадрат максимального периметра задается точками: "
        <<points[pointsOfMaxSquare[0]]
        <<points[pointsOfMaxSquare[1]]
        <<points[pointsOfMaxSquare[2]]
        <<points[pointsOfMaxSquare[3]]<<endl;
        cout<<"Его периметр равен: "<<max*4;
    }else
    {
        cout<<"В списке нет таких 4х точек, которые бы задавали квадрат."<<endl;
    }
    
    
}