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

template<typename T>
T read(bool(*predicate)(T,T),T arg = 0)
{
    T x = 0;
    cin >> x;
    while((cin.fail())|| !predicate(x,arg))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        cin >> x;
    }
    return x;
}

template<typename T>
bool all(T a,T arg)
{
  return true;
}

template<typename T>
bool notNull(T a,T arg)
{
  return abs(a) > numeric_limits<float>::epsilon()*100;
}

template<typename T>
bool positive(T a,T arg)
{
  return a > 0;
}

struct stack
{
    int data;
    stack* next;
};

void push(stack*& st, int data)
{
    stack* tmp = new stack;
    tmp->next = st;
    st = tmp;
    st->data = data;
}

int pop(stack*& st)
{
    int data = st->data;
    stack* tmp = st;
    st = st->next;
    delete tmp;
    return data;
}

stack* from_random(int n,int a,int b)
{
    stack* st = new stack;
    st->data = rand() % (b - a) + a;
    st->next = nullptr;
    stack* ptr = st;
    while(n)
    {
        push(st,rand() % (b - a) + a);
        n--;
    }
    return st;
}

stack* from_kb(int n)
{
    stack* st = new stack;
    st->data = read<int>(all);
    st->next = nullptr;
    stack* ptr = st;
    while(n)
    {
        push(st,read<int>(all));
        n--;
    }
    return st;
}

stack* from_file(int n)
{
    ifstream file("input.txt");
    stack* st = new stack;
    int num;
    file >> num;
    st->data = num;
    st->next = nullptr;
    stack* ptr = st;
    n--;
    while(n)
    {
        file >> num;
        push(st,num);
        n--;
    }
    return st;
}

void print_stack(stack* st)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOutput, 12);
    cout << st->data << endl;
    SetConsoleTextAttribute(hOutput, 15);
    st = st->next;
    while(st)
    {
        cout << st->data << endl;
        st = st->next;
    }
}

bool is_prime(int number)
{

    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return false;
    }
    return true;
}

void remove_primes(stack*& st)
{
    stack* new_st = new stack;
    new_st->next = nullptr;
    int num = pop(st);
    while(st && is_prime(num))
    {
        num = pop(st);
    }
    new_st->data = num;
    while(st)
    {
        num = pop(st);
        if(!is_prime(num)) push(new_st,num);
    }
    st = new_st;
}

struct queue
{
    int data;
    queue* next;
};

void q_push(queue*& end, int data)
{
    queue* tmp = new queue;
    end->next = tmp;
    end = tmp;
    end->data = data;
    end->next = nullptr;
}

int q_pop(queue*& begin)
{
    int data = begin->data;
    queue* tmp = begin;
    begin = begin->next;
    delete tmp;
    return data;
}

queue* q_from_random(int n,int a,int b,queue*& end)
{
    queue* st = new queue;
    st->data = rand() % (b - a) + a;
    st->next = nullptr;
    end = st;
    while(n)
    {
        q_push(end,rand() % (b - a) + a);
        n--;
    }
    return st;
}

queue* q_from_kb(int n,queue*& end)
{
    queue* st = new queue;
    st->data = read<int>(all);
    st->next = nullptr;
    end = st;
    while(n)
    {
        q_push(end,read<int>(all));
        n--;
    }
    return st;
}

queue* q_from_file(int n,queue*& end)
{
    ifstream file("input.txt");
    int num;
    file >> num;
    queue* st = new queue;
    st->data = num;
    st->next = nullptr;
    end = st;
    n--;
    while(n)
    {
        file >> num;
        q_push(end,num);
        n--;
    }
    return st;
}

void print_queue(queue* begin)
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOutput, 12);
    cout << begin->data << " ";
    SetConsoleTextAttribute(hOutput, 15);
    begin = begin->next;
    while(begin)
    {
        cout << begin->data << " ";
        begin = begin->next;
    }
    cout << endl;
}

void insert_second_after_max_in_first(queue*& first,queue* second,queue* second_end)
{
    queue* max = first;
    queue* ptr = first;
    while(ptr)
    {
        if(ptr->data > max->data) max = ptr;
        ptr = ptr->next;
    }
    second_end->next = max->next;
    max->next = second;
}

int main()
{
    system("chcp 65001");
    cout << "Ввести контейнеры:\n1.случайно\n2.с клавиатуры\n3.из файла";
    int choice = 3; //read<int>(positive);

    stack* first_stack;
    queue* first_queue_begin;
    queue* second_queue_begin;
    queue* first_queue_end;
    queue* second_queue_end;

    switch (choice)
    {
    case 1:
    first_stack = from_random(10,0,10);
    first_queue_begin = q_from_random(10,0,10,first_queue_end);
    second_queue_begin = q_from_random(10,0,10,second_queue_end);
        break;
    case 2:
    first_stack = from_kb(10);
    first_queue_begin = q_from_kb(10,first_queue_end);
    second_queue_begin = q_from_kb(10,second_queue_end);
        break;
    case 3:
    first_stack = from_file(10);
    first_queue_begin = q_from_file(10,first_queue_end);
    second_queue_begin = q_from_file(10,second_queue_end);
        break;
    default:
        break;
    }
    cout << "Содержимое стека до операции:" << endl;
    print_stack(first_stack);
    cout << "Содержимое 1 очереди до операции:" << endl;
    print_queue(first_queue_begin);
    cout << "Содержимое 2 очереди до операции:" << endl;
    print_queue(second_queue_begin);

    remove_primes(first_stack);
    insert_second_after_max_in_first(first_queue_begin,second_queue_begin,second_queue_end);

    cout << "Содержимое стека после операции:" << endl;
    print_stack(first_stack);
    cout << "Содержимое 1 очереди после операции:" << endl;
    print_queue(first_queue_begin);
    system("pause");
    return 0;
}