#if !defined(SCANNER_H)
#define SCANNER_H

#include <vector>
#include <string>

struct scanner
{
    char model[25];
    int price;
    double x_size;
    double y_size;
    int optr;
    int grey;
};

enum scanner_traits
{
    price,
    grey
};

void append(std::string filename, std::vector<scanner> v);
void sort_by(std::string filename, scanner_traits tr);
void print(std::string filename);

#endif // SCANNER_H
