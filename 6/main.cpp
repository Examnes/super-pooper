#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
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
bool answer(T a,T b)
{
  return a >= '0' && a <= '6'; 
}

template<typename T>
bool all(T a,T b)
{
  return true; 
}

bool is_full_square(uint32_t a)
{
 return (sqrt(a) == floor(sqrt(a)));
}

template<typename T>
struct node
{
  node* next;
  T data;
};

template<typename T>
struct list
{
  node<T>* begin;
};

template<typename T>
list<T> list_init()
{
  list<T> l;
  l.begin = nullptr;
  return l;
}

template<typename T>
void list_push_back(list<T>& l,T data)
{
  node<T>* new_begin = new node<T>;
  new_begin->data = data;
  if(l.begin)
  {
    new_begin->next = l.begin;
  }else
  {
    new_begin->next = nullptr;
  }
  
  l.begin = new_begin;
  
}

template<typename T>
bool list_insert(list<T>& l, size_t at, T data)
{
  if(!l.begin) return false;
  node<T>* n = l.begin;
  size_t i = 0;
  while(n && i < at)
  {
    i++;
    n = n->next;
  }
  if(!n) return false;
  node<T>* inserted = new node<T>;
  inserted->data = data;
  inserted->next = n->next;
  n->next = inserted;
  return true;
}

template<typename T>
void list_print(list<T>& l)
{
  node<T>* node = l.begin;
  cout << "#" << node << " = " << node->data << " <- head" << endl;
  node = node->next;
  while(node)
  {
    cout << "#" << node << " = " << node->data << endl;
    node = node->next;
  }
}

template<typename T>
T list_pull(list<T>& l)
{
  if(!l.begin) 
  {
    return (T)NULL;
  }
  T data = l.begin->data;
  node<T>* temp = l.begin;
  if(!l.begin->next)
  {
    l.begin = nullptr;
  }else
  {
    l.begin = l.begin->next;
  }
  delete temp;
  return data;
}

template<typename T>
bool list_remove(list<T>& l,size_t at)
{
  if(!at) return true | list_pull(l);
  node<T>* next = l.begin;
  node<T>* prev = next;
  size_t i = 0;
  while((i < at) && (next != nullptr))
  {
    i++;
    prev = next;
    next = next->next;
  };
  if(i == at)
  {
    prev->next = next->next;
    delete next;
    return true;
  }
  return false;
}


template<typename T>
bool list_is_empty(list<T>& l)
{
  return l.begin == nullptr;
}

template<typename T>
int list_indexof(list<T>& l,T x)
{
  int i = 0;
  node<T>* n = l.begin;
  while(n && n->data != x)
  {
    n = n->next;
    i++;
  }
  if(n) return i;
  return -1;
}


template<typename T>
bool list_at(list<T>& l,size_t at,T& result)
{
  if(!l.begin) return false;
  node<T>* n = l.begin;
  size_t i = 0;
  while(n && i < at)
  {
    i++;
    n = n->next;
  }
  if(!n) return false;
  result = n->data;
  return true;
}

bool isFibonacci(uint32_t n) 
{ 
    return is_full_square(5*n*n + 4) || 
           is_full_square(5*n*n - 4); 
} 


void insert_after_fibonacci(list<uint32_t> l,uint32_t element)
{
  size_t i = 0;
  uint32_t at;
  while(list_at(l,i,at))
  {
    if(isFibonacci(at))
      list_insert(l,i,element);
    i++;
  }
}

bool insert_after_min_full_square(list<uint32_t> l,uint32_t element)
{
  uint32_t at;
  bool finded = false;
  int min = -1;
  size_t i = 0;
  while(list_at(l,i,at))
  {
    if(is_full_square(at) && at < min)
    {
      min = at;
      finded = true;
    }
    i++;
  }
  if(finded) list_insert<uint32_t>(l,i,element);
  return finded;
}

void remove_dividable(list<uint32_t> l,uint32_t divisor)
{
  size_t i = 0;
  uint32_t at;
  while(list_at(l,i,at))
  {
    if(at % divisor == 0)
    {
      list_remove<uint32_t> (l,i);
      i--;
    }
    i++;
  }
}

int main(int argc,char** argv)
{
  system("chcp 1251");
  list<uint32_t> l = list_init<uint32_t>();
  char user_answer = 0;
  cout << "��� ��������� ��������� ������ �������� ��� ������� �������. ��� �������� ���������� ����� ����� ��������� ����� ����������� �� ������ ���������, ���� ������������ �� �������� �������� ������� ����� ����� ��������� ��� ���� � ������ ����� ��� ������ ���������.\n";
  cout << "��� �������� �������� ��������� ������ ��� �����, ������� ����, ��� ������ ������������, � ��� �� ��������� ������� ������������ �������.\n";
  user_answer = read<char>(all);
  if(tolower(user_answer) == 'y')
  {
    ifstream file("input.txt");
    uint32_t datam;
    file>>datam;
    list_push_back<uint32_t>(l,datam);
    while(!file.eof())
    {
      file>>datam;
      list_push_back<uint32_t>(l,datam);
    }
  }
  user_answer = 0;
  do
  {
      cout 
      << "������� ����� ��������:" << endl
        << "1.�������� �������" << endl
        << "2.������� �������" << endl
        << "3.�������" << endl
        << "4.�����" << endl
        << "5.�������� ����� � �� (1.1 1.2)" << endl
        << "6.������� (2)" << endl
        << "0.�����" << endl;
      
      char user_answer = read<char>(answer);
      switch(user_answer)
      {
        case '1':
        {
          cout << "��� ��������?" << endl;
          uint32_t element = read<uint32_t>(all);
          list_push_back<uint32_t> (l,element);
        }
        break;

        case '2':
        {
          uint32_t element = list_pull<uint32_t>(l);
          cout << "����������� ������� - " << element << endl;
        }
        break;

        case '3':
          cout << "������: " << endl;
          list_print(l);
        break;

        case '4':
        {
          cout << "��� �����?" << endl;
          uint32_t element = read<uint32_t>(all);
          uint32_t index = list_indexof<uint32_t>(l,element);
          if(index != -1){cout << "��� ������ - " << index << endl;} else cout << "����� ���." << endl;
        }
        break;

        case '5':
        {
          cout << "��� ��������?" << endl;
          uint32_t element = read<uint32_t>(all);
          cout << "Y ������� ����� �������� ���������� ���������\n";
          char opinion = read<char>(all);
          bool finded = false;
          if(tolower(opinion) != 'y')
          {
            finded = insert_after_min_full_square(l,element);
          }else insert_after_fibonacci(l,element);
          if(!finded && tolower(opinion) != 'y')
          {
            cout << "���� ��������?" << endl;
            uint32_t index = read<uint32_t>(all);
            if(!list_insert<uint32_t> (l,index,element)) cout << "������� ������� ������" << endl;
          }
        }
        break;

        case '6':
        {  
          cout << "������� ���� �������?\n";
          uint32_t a = read<uint32_t>(all);
          remove_dividable(l,a);
        }
        break;

        case '0':
          cout << "exit" << endl;
          return 0;
        break;	

      }
  }while(user_answer != '0' && !list_is_empty<uint32_t> (l));
}
