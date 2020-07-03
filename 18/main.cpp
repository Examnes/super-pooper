#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template <typename T>
T read(bool (*predicate)(T, T), T arg = 0)
{
    T x = 0;
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
bool all(T a, T arg)
{
    return true;
}

template <typename T>
bool notNull(T a, T arg)
{
    return abs(a) > numeric_limits<float>::epsilon() * 100;
}

template <typename T>
bool positive(T a, T arg)
{
    return a > 0;
}

class big
{
private:
    bool negative;
public:
    vector<uint16_t> digits;
    big(string s);
    big()
    {
    }
    ~big();
    friend const big operator+(const big &left, const big &right);
    friend const big operator-(big left, big right);
    friend bool operator<(const big &left, const big &right);
    friend bool operator==(const big &left, const big &right);
    const big operator+() const;
    const big operator-() const;
};

const big big::operator+() const
{
    return big(*this);
}

const big big::operator-() const
{
    big copy(*this);
    copy.negative = !copy.negative;
    return copy;
}

bool operator==(const big &left, const big &right)
{
    if (left.negative != right.negative)
        return false;
    if (left.digits.empty())
    {
        if (right.digits.empty() || (right.digits.size() == 1 && right.digits[0] == 0))
            return true;
        else
            return false;
    }

    if (right.digits.empty())
    {
        if (left.digits.size() == 1 && left.digits[0] == 0)
            return true;
        else
            return false;
    }
    if (left.digits.size() != right.digits.size())
        return false;
    for (size_t i = 0; i < left.digits.size(); ++i)
        if (left.digits[i] != right.digits[i])
            return false;

    return true;
}

bool operator<(const big &left, const big &right)
{
    if (left == right)
        return false;
    if (left.negative)
    {
        if (right.negative)
            return ((-right) < (-left));
        else
            return true;
    }
    else if (right.negative)
        return false;
    else
    {
        if (left.digits.size() != right.digits.size())
        {
            return left.digits.size() < right.digits.size();
        }
        else
        {
            for (long long i = left.digits.size() - 1; i >= 0; --i)
            {
                if (left.digits[i] != right.digits[i])
                    return left.digits[i] < right.digits[i];
            }

            return false;
        }
    }
}

const big operator-(big left, big right)
{
    if (right.negative)
        return left + (-right);
    else if (left.negative)
        return -(-left + right);
    else if (left < right)
        return -(right - left);
    int carry = 0;
    big res;
    int base = 10;
    for (size_t i = 0; i < right.digits.size() || carry != 0; ++i)
    {
        res.digits.push_back((i < left.digits.size() ? left.digits[i] : 0) + carry - (i < right.digits.size() ? right.digits[i] : 0));
        carry = res.digits[i] < 0;
        if (carry != 0)
            res.digits[i] += 10;
    }
    return res;
}

const big operator+(const big &left, const big &right)
{
    if (left.negative)
    {
        if (right.negative)
            return -(-left + (-right));
        else
            return right - (-left);
    }
    else if (right.negative)
        return left - (-right);
    int carry = 0;
    big res;
    int base = 10;
    for (size_t i = 0; i < max(left.digits.size(), right.digits.size()) || carry; i++)
    {
        if (i == res.digits.size())
            res.digits.push_back(0);
        res.digits[i] = ((i < left.digits.size() ? left.digits[i] : 0) + carry + (i < right.digits.size() ? right.digits[i] : 0));
        carry = res.digits[i] >= base;
        if (carry)
            res.digits[i] -= base;
    }
    return res;
}

big::big(string s)
{
    negative = false;
    for (auto c : s)
    {
        if (isdigit(c))
        {
            digits.push_back(c - 48);
        }
        else
        {
            if (c == '-')
                negative = true;
        }
    }
}

big::~big()
{
}

int main()
{
    system("chcp 65001");
    string first_s;
    string second_s;
    cout << "Введите первое число" << endl;
    cin >> first_s;
    cout << "Введите второе число" << endl;
    cin >> second_s;
    big first(first_s),second(second_s);
    big res = first + second;
    int sum = 0;
    for(auto a : res.digits)
        sum += a;
    cout << "Среднее арифметическе: " << (float)sum / res.digits.size() << endl;
    system("pause");
    return 0;
}
