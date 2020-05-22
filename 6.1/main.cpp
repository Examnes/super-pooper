#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
using namespace std;

class doublelist
{
private:
  struct node
  {
    node *next;
    node *previous;
    uint32_t data;
  };

  node *begin;

public:
  void push_back(uint32_t data)
  {
    node *n = new node;
    n->data = data;
    n->previous = nullptr;
    n->next = begin;
    if(begin) begin->previous = n;
    begin = n;
  }

  uint32_t pop_back()
  {
    uint32_t data = begin->data;
    node *temp = begin;
    begin = begin->next;
    begin->previous = nullptr;
    delete temp;
    return data;
  }

  void insert(uint32_t data, size_t at)
  {
    node *n = begin;
    while (n && at > 0)
    {
      n = n->next;
      at--;
    }
    if (at * at)
      return;
    node *temp = new node;
    temp->data = data;
    temp->next = n->next;
    temp->previous = n;
    if (n->next)
      n->next->previous = temp;
    n->next = temp;
  }

  void insert_before(uint32_t data, size_t at)
  {
    node *n = begin;
    while (n && at > 0)
    {
      n = n->next;
      at--;
    }
    if (at * at)
      return;

    node* temp2 = new node;
    temp2->data = data;
    temp2->next = n;
    temp2->previous = n->previous;
    if(n->previous) {n->previous->next = temp2;} else {begin = temp2;}
    n->previous = temp2;
  }

  void remove(size_t at)
  {
    node *n = begin;
    while (n && at)
    {
      n = n->next;
      at--;
    }
    if (at * at != 0)
      return;
    node *next_node = n->next;
    node *prev_node = n->previous;
    if (next_node)
      next_node->previous = prev_node;
    if (prev_node)
    {
      prev_node->next = next_node;
    }
    else
      begin = next_node;
    delete n;
  }

  void push_front(uint32_t data)
  {
    node *end = begin;
    while (end->next)
      end = end->next;

    end->next = new node;
    end->next->next = nullptr;
    end->next->previous = end;
    end->next->data = data;
    end = end->next;
  }

  uint32_t pop_front()
  {
    node *end = begin;
    while (end->next)
      end = end->next;

    uint32_t data = end->data;
    node *temp = end;
    end->previous->next = nullptr;
    delete temp;
    return data;
  }

  uint32_t &operator[](const int index)
  {
    node *n = begin;
    uint32_t at = index;
    while (n && at)
    {
      n = n->next;
      at--;
    }
    return n->data;
  }

  void print()
  {
    node *n = begin;
    cout << "#" << n << " = " << n->data << "<-- head" << endl;
    n = n->next;
    while (n)
    {
      cout << "#" << n << " = " << n->data << endl;
      n = n->next;
    }
  }

  bool empty()
  {
    return !begin;
  }

  int indexof(uint32_t data)
  {
    node *n = begin;
    int i = 0;
    while (n && n->data != data)
    {
      n = n->next;
      i++;
    }
    if (n)
      return i;
    return -1;
  }

  int size()
  {
    node *n = begin;
    int i = 0;
    while (n)
    {
      n = n->next;
      i++;
    }
    return i;
  }

  doublelist();
  ~doublelist();
};

doublelist::doublelist()
{
  begin = nullptr;
}

doublelist::~doublelist()
{
}

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
bool answer(T a, T b)
{
  return a >= '0' && a <= '6';
}

template <typename T>
bool all(T a, T b)
{
  return true;
}

bool is_full_square(uint32_t a)
{
  return (sqrt(a) == floor(sqrt(a)));
}

bool isFibonacci(uint32_t n)
{
  return is_full_square(5 * n * n + 4) ||
         is_full_square(5 * n * n - 4);
}

void insert_after_fibonacci(doublelist l,uint32_t element)
{
  size_t i = 0;
  while(i < l.size())
  {
    if(isFibonacci(l[i]))
    {
      l.insert(element,i);
      l.insert_before(element,i);
      i++;
    }
    i++;
  }
}

bool insert_after_min_full_square(doublelist l,uint32_t element)
{
  uint32_t at;
  bool finded = false;
  int min = -1;
  size_t i = 0;
  while(i < l.size())
  {
    if(is_full_square(l[i]) && l[i] < min)
    {
      min = l[i];
      finded = true;
    }
    i++;
  }
  if(finded)
  {
    l.insert(element,i);
    l.insert_before(element,i);
  }
  return finded;
}

void remove_dividable(doublelist l,uint32_t divisor)
{
  size_t i = 0;
  while(i < l.size())
  {
    if(l[i] % divisor == 0)
    {
      l.remove(i);
      i--;
    }
    i++;
  }
}

int main(int argc, char **argv)
{
  system("chcp 1251");
  cout << "эта программа позволяет делать операции над связным списком. При операции добавления число будет добавлено после наименьшего из полных квадратов, если пользователь не пожелает добавить элемент после чисел фибоначчи или если в списке вовсе нет полных квадратов.\n";
  cout << "при операции удаления программа удалит все числа, кратные тому, что введет пользователь, а так же предложит удалить произвольный элемент.\n";
 
  doublelist lst = doublelist();

  char user_answer;
  cout << "Y      input.txt\n";
  user_answer = read<char>(all);
  if (tolower(user_answer) == 'y')
  {
    ifstream file("input.txt");
    uint32_t datam;
    file >> datam;
    lst.push_back(datam);
    while (!file.eof())
    {
      file >> datam;
      lst.push_back(datam);
    }
  }
  user_answer = 0;

  do
  {
    cout
        << "Операции:" << endl
        << "1.Вставить в начале и в конце" << endl
        << "2.Удалитьв начале ив конце" << endl
        << "3.вывести" << endl
        << "4.найти" << endl
        << "5.Выполнить задания (1.1 1.2)" << endl
        << "6.выполнить задание (2)" << endl
        << "0.выйти" << endl;

    char user_answer = read<char>(answer);
    switch (user_answer)
    {
    case '1':
    {
      cout << "что вставлять?" << endl;
      uint32_t element = read<uint32_t>(all);
      lst.push_back(element);
      lst.push_front(element);
    }
    break;

    case '2':
    {
      lst.pop_back();
      lst.pop_front();
    }
    break;

    case '3':
      cout << "список: " << endl;
      lst.print();
      break;

    case '4':
    {
      cout << "что искать?" << endl;
      uint32_t element = read<uint32_t>(all);
      uint32_t index = lst.indexof(element);
      if (index != -1)
      {
        cout << "индекс найденного элемента: " << index << endl;
      }
      else
        cout << "таких в списке нет" << endl;
    }
    break;

    case '5':
    {
      cout << "что вставлять" << endl;
      uint32_t element = read<uint32_t>(all);
      cout << "Y если хотите вставить после чисел фибоначчи\n";
      char opinion = read<char>(all);
      bool finded = false;
      if(tolower(opinion) != 'y')
      {
        finded = insert_after_min_full_square(lst,element);
      }else insert_after_fibonacci(lst,element);
      if(!finded && tolower(opinion) != 'y')
      {
        cout << "полных квадратов нет, где хотите вставить?" << endl;
        uint32_t index = read<uint32_t>(all);
        if(index > lst.size()){cout << "индекс слишком большой" << endl;} 
        else lst.insert(element,index);
      }
    }
    break;

    case '6':
    {
      cout << "кратное чему удалить?\n";
      uint32_t a = read<uint32_t>(all);
      remove_dividable(lst,a);
    }
    break;

    case '0':
      cout << "exit" << endl;
      return 0;
      break;
    }
  } while (user_answer != '0' && !lst.empty());

  return 0;
}
