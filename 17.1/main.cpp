#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <cmath>
#include <array>
#include <windows.h>

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

bool is_prime(int number)
{

    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    for (int i = 3; (i * i) <= number; i += 2)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

class stack
{
private:
    int *arr;
    int top;
    int sz;
    void swap(stack& other)
    {
        std::swap(top,other.top);
        std::swap(sz,other.sz);
        std::swap(arr,other.arr);
    }
public:
    void push(int data);
    int pop();
    void print();
    stack();
    stack(const stack &another);
    bool is_empty();
    const stack &operator=(const stack & other)
    {
        stack temp(other);
        swap(temp);
        return *this;
    }
    ~stack();
};

stack::stack()
{
    arr = new int[10];
    top = 0;
    sz = 10;
}

stack::stack(const stack &another)
{
    top = another.top;
    arr = new int[another.sz];
    sz = another.sz;
    copy(another.arr, another.arr + another.top, arr);
}

stack::~stack()
{
    delete[] arr;
}

bool stack::is_empty()
{
    return top == 0;
}

void stack::push(int data)
{
    arr[top++] = data;
    if (top == sz)
    {
        int *tmp = new int[sz + 10];
        copy(arr, arr + sz, tmp);
        delete arr;
        arr = tmp;
    }
}

int stack::pop()
{
    if (top)
    {
        return arr[--top];
    }
    return 0;
}

void stack::print()
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOutput, 12);
    cout << arr[0] << endl;
    SetConsoleTextAttribute(hOutput, 15);
    for (int i = 1; i < top; i++)
    {
        cout << arr[i] << endl;
    }
}

stack remove_primes(stack st)
{
    stack new_st = stack();
    int num = st.pop();
    while (!st.is_empty() && is_prime(num))
    {
        num = st.pop();
    }
    if (!st.is_empty())
        new_st.push(num);
    while (!st.is_empty())
    {
        num = st.pop();
        if (!is_prime(num))
            new_st.push(num);
    }
    return new_st;
}

class queue
{
private:
    int *arr;
    int head;
    int tail;
    int sz;

public:
    void push(int data);
    int pop();
    void print();
    queue();
    queue(const queue &another);
    bool is_empty();
    ~queue();
    int getmax();
    void swap(queue& other)
    {
        std::swap(head,other.head);
        std::swap(tail,other.tail);
        std::swap(sz,other.sz);
        std::swap(arr,other.arr);
    }
    const queue &operator=(const queue & other)
    {
        queue temp(other);
        swap(temp);
        return *this;
    }
};

queue::queue(const queue &another)
{
    head = 0;
    arr = new int[another.tail - another.head];
    sz = another.tail - another.head;
    tail = another.tail - another.head;
    copy(another.arr + another.head, another.arr + another.head + another.tail, arr);
}

queue::~queue()
{
    delete[] arr;
}

queue::queue()
{
    arr = new int[10];
    sz = 10;
    head = 0;
    tail = 0;
}

bool queue::is_empty()
{
    return tail == head;
}

void queue::push(int data)
{
    arr[tail++] = data;
    if (tail == sz)
    {
        if (tail - head != sz)
        {
            move(arr + head, arr + tail, arr);
            tail = tail - head;
            head = 0;
        }
        else
        {
            int *tmp = new int[sz + 10];
            copy(arr + head, arr + tail, tmp);
            delete[] arr;
            arr = tmp;
            tail = tail - head;
            head = 0;
        }
    }
}

int queue::pop()
{
    if (tail != head)
    {
        return arr[head++];
    }
    return 0;
}

void queue::print()
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOutput, 12);
    cout << arr[0] << endl;
    SetConsoleTextAttribute(hOutput, 15);
    for (int i = head; i < tail; i++)
    {
        cout << arr[i] << endl;
    }
}

int queue::getmax()
{
    int maximum = arr[head];
    for(int i = head;i < tail;i++)
        if(maximum < arr[i]) maximum = arr[i];
    return maximum;
}

queue insert_second_after_max_in_first(queue first,queue second)
{
    int maximum = first.getmax();
    int num = first.pop();
    queue res = queue();
    while(num != maximum)
    {
        res.push(num);
        num = first.pop();
    }
    res.push(num);
    while(!second.is_empty())
    {
        res.push(second.pop());
    }
    while(!first.is_empty())
    {
        res.push(first.pop());
    }
    return res;
}

queue q_from_random(int n,int a,int b)
{
    queue st = queue();
    while(n)
    {
        st.push(rand() % (b - a) + a);
        n--;
    }
    return st;
}

queue q_from_kb(int n)
{
    queue st = queue();
    while(n)
    {
        st.push(read<int>(all));
        n--;
    }
    return st;
}

queue q_from_file(int n)
{
    ifstream file("input.txt");
    int num;
    queue st = queue();
    while(n)
    {
        file >> num;
        st.push(num);
        n--;
    }
    return st;
}

stack from_random(int n,int a,int b)
{
    stack st = stack();
    while(n)
    {
        st.push(rand() % (b - a) + a);
        n--;
    }
    return st;
}

stack from_kb(int n)
{
    stack st = stack();
    while(n)
    {
        st.push(read<int>(all));
        n--;
    }
    return st;
}

stack from_file(int n)
{
    ifstream file("input.txt");
    int num;
    stack st = stack();
    while(n)
    {
        file >> num;
        st.push(num);
        n--;
    }
    return st;
}

int main()
{
    system("chcp 65001");
    cout << "Ввести контейнеры:\n1.случайно\n2.с клавиатуры\n3.из файла\n";
    int choice = 3; //read<int>(positive);

    stack first_stack;
    queue first_queue;
    queue second_queue;

    switch (choice)
    {
    case 1:
        first_stack = from_random(10, 0, 10);
        first_queue = q_from_random(10, 0, 10);
        second_queue = q_from_random(10, 0, 10);
        break;
    case 2:
        first_stack = from_kb(10);
        first_queue = q_from_kb(10);
        second_queue = q_from_kb(10);
        break;
    case 3:
        first_stack = from_file(10);
        first_queue = q_from_file(10);
        second_queue = q_from_file(10);
        break;
    default:
        break;
    }
    cout << "Содержимое стека до операции:" << endl;
    first_stack.print();
    cout << "Содержимое 1 очереди до операции:" << endl;
    first_queue.print();
    cout << "Содержимое 2 очереди до операции:" << endl;
    second_queue.print();

    first_stack = remove_primes(first_stack);
    first_queue = insert_second_after_max_in_first(first_queue, second_queue);

    cout << "Содержимое стека после операции:" << endl;
    first_stack.print();
    cout << "Содержимое 1 очереди после операции:" << endl;
    first_queue.print();
    system("pause");
    return 0;
}