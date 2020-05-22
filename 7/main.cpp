#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
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
bool answer(T a, T b)
{
    return a >= 0 && a <= 5;
}

template <typename T>
bool all(T a, T b)
{
    return true;
}

template <typename T>
bool greather(T a, T arg)
{
    return a > arg;
}

template <typename T>
bool lower(T a, T arg)
{
    return a < arg;
}

const int cM = 4;
const int cN = 5;

template <typename T>
void print_any_matrix(const T arr, const size_t M, const size_t N)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

template <typename T>
void fill_from_random(T &arr, const size_t M, const size_t N, int a, int b)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = a + rand() % (b - a);
        }
    }
}

template <typename T>
bool fill_from_file(T &arr, const size_t M, const size_t N, string filename)
{
    ifstream file = ifstream(filename);
    if (!file)
        return false;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!file.eof())
            {
                file >> arr[i][j];
            }
            else
                return false;
        }
    }
    file.close();
    return true;
}

template <typename T>
int find_first_repeting_column(T arr, const size_t M, const size_t N)
{
    int found = -1;
    for (int i = N - 1; i >= 0; i--)
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < M; k++)
            {
                if (arr[j][i] == arr[k][i] && j != k)
                {
                    found = i;
                }
            }
        }
    return found;
}

template <typename T>
void replace_below_seconady_with_squares(T &arr, const size_t M)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < i; j++)
        {
            arr[M - j - 1][i + 1] = arr[M - j - 1][i + 1] * arr[M - j - 1][i + 1];
        }
    }
}

int get_situbale_colum_count4(int **arr, const size_t M, const size_t N)
{
    int count = 0;
    for (size_t j = 0; j < N; j++)
    {
        bool situable = true;
        for (size_t i = 0; i < M; i++)
        {
            if (arr[i][j] < 0)
                situable = false;
        }
        if (situable)
            count++;
    }
    return count;
}

int get_situbale_row_count4(int **arr, const size_t M, const size_t N)
{
    int count = 0;
    for (size_t i = 0; i < M; i++)
    {
        bool situable = true;
        for (size_t j = 0; j < N; j++)
        {
            if (arr[i][j] > 0)
                situable = false;
        }
        if (situable)
            count++;
    }
    return count;
}

void insert_situable_columns4(int **arr, int **new_arr, size_t M, size_t N)
{
    int ptr = 0;
    for (size_t j = 0; j < N; j++)
    {
        bool situable = true;
        for (size_t i = 0; i < M; i++)
        {
            if (arr[i][j] < 0)
                situable = false;
        }
        if (situable)
        {
            for (size_t i = 0; i < M; i++)
            {
                new_arr[i][ptr] = arr[i][M - 1];
            }
            ptr++;
        }
        for (size_t i = 0; i < M; i++)
        {
            new_arr[i][ptr] = arr[i][j];
        }
        ptr++;
    }
}

void insert_situable_rows4(int **arr, int **new_arr, size_t M, size_t N)
{
    cout << "Введите номер вставляемого столбца" << endl;
    int choise = read<int>(lower, M);
    int ptr = 0;
    for (size_t i = 0; i < M; i++)
    {
        bool situable = true;
        for (size_t j = 0; j < N; j++)
        {
            if (arr[i][j] > 0)
                situable = false;
        }
        if (situable)
        {
            for (size_t j = 0; j < N; j++)
            {
                if (arr[i][j] > 0)
                    situable = false;
                new_arr[ptr][j] = arr[choise][j];
            }
            ptr++;
        }
        for (size_t j = 0; j < N; j++)
        {
            new_arr[ptr][j] = arr[i][j];
        }
        ptr++;
    }
}

template <typename T>
int findMax(T mat, int M, int N)
{
    int maxElement = mat[0][0];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] > maxElement)
            {
                maxElement = mat[i][j];
            }
        }
    }
    return maxElement;
}

template <typename T>
int findMin(T mat, int M, int N)
{
    int maxElement = mat[0][0];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] < maxElement)
            {
                maxElement = mat[i][j];
            }
        }
    }
    return maxElement;
}

int get_situbale_colum_count5(int **arr, const size_t M, const size_t N)
{
    int count = 0;
    int max = findMax(arr, M, N);
    for (size_t j = 0; j < N; j++)
    {
        bool situable = false;
        for (size_t i = 0; i < M; i++)
        {
            if (arr[i][j] == max)
                situable = true;
        }
        if (situable)
            count++;
    }
    return count;
}

int get_situbale_row_count5(int **arr, const size_t M, const size_t N)
{
    int count = 0;
    int min = findMin(arr, M, N);
    for (size_t i = 0; i < M; i++)
    {
        bool situable = false;
        for (size_t j = 0; j < N; j++)
        {
            if (arr[i][j] == min)
                situable = true;
        }
        if (situable)
            count++;
    }
    return count;
}

void remove_situable_columns5(int **arr, int **new_arr, size_t M, size_t N)
{
    int ptr = 0;
    int max = findMax(arr, M, N);
    for (size_t j = 0; j < N; j++)
    {
        bool situable = false;
        for (size_t i = 0; i < M; i++)
        {
            if (arr[i][j] == max)
                situable = true;
        }
        if (!situable)
        {
            for (size_t i = 0; i < M; i++)
            {
                new_arr[i][ptr] = arr[i][j];
            }
            ptr++;
        }
    }
}

void remove_situable_rows5(int **arr, int **new_arr, size_t M, size_t N)
{
    int ptr = 0;
    int min = findMin(arr, M, N);
    for (size_t i = 0; i < M; i++)
    {
        bool situable = false;
        for (size_t j = 0; j < N; j++)
        {
            if (arr[i][j] == min)
                situable = true;
        }
        if (!situable)
        {
            for (size_t j = 0; j < N; j++)
            {
                new_arr[ptr][j] = arr[i][j];
            }
            ptr++;
        }
    }
}

void enterMN(size_t& M,size_t& N)
{
    cout << "Введите количество строк" << endl;
    M = read<size_t>(all);
    cout << "Введите количество столбцов" << endl;
    N = read<size_t>(all);
}


int main()
{
    system("chcp 65001");
    int choise;
    while (choise != '0')
    {
        cout << "Введите номер задания или 0 чтобы выйти" << endl;
        choise = read<int>(answer);
        switch (choise)
        {
        case 1:
        {
            int c_array[cM][cN];
            array<array<int, cM>, cN> stl_array;
            cout << "Введите больше какого числа нужно найтив матрице" << endl;
            int g = read<int>(all);
            cout << "Нажмите Y чтобы заполнить матрицу из файла" << endl;
            char choise;
            cin >> choise;
            vector<int> arr(cM);
            if (tolower(choise) == 'y')
            {
                cout << "Введите имя файла" << endl;
                string filename;
                cin >> filename;
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                if (tolower(choise) == 'y')
                {
                    if (!fill_from_file(stl_array, cM, cN, filename))
                    {
                        cout << "Не удалось считать данные из файла, возможно их недостаточно или файл не существует" << endl;
                        return -1;
                    }
                    print_any_matrix(stl_array, cM, cN);
                    for (int i = 0; i < cM; i++)
                        for (int j = 0; j < cN; j++)
                        {
                            if (stl_array[i][j] > g)
                                arr[i]++;
                        }
                }
                else
                {
                    if (!fill_from_file(c_array, cM, cN, filename))
                    {
                        cout << "Не удалось считать данные из файла, возможно их недостаточно или файл не существует" << endl;
                        return -1;
                    }
                    print_any_matrix(c_array, cM, cN);
                    for (int i = 0; i < cM; i++)
                        for (int j = 0; j < cN; j++)
                        {
                            if (c_array[i][j] > g)
                                arr[i]++;
                        }
                }
            }
            else
            {
                cout << "Введите границы рандома" << endl;
                int a, b;
                a = read<int>(all);
                b = read<int>(greather, a);

                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    fill_from_random(stl_array, cM, cN, a, b);
                    print_any_matrix(stl_array, cM, cN);
                    for (int i = 0; i < cM; i++)
                        for (int j = 0; j < cN; j++)
                        {
                            if (stl_array[i][j] > g)
                                arr[i]++;
                        }
                }
                else
                {
                    fill_from_random(c_array, cM, cN, a, b);
                    print_any_matrix(c_array, cM, cN);
                    for (int i = 0; i < cM; i++)
                        for (int j = 0; j < cN; j++)
                        {
                            if (c_array[i][j] > g)
                                arr[i]++;
                        }
                }
            }
            cout << "Результат" << endl;
            for (auto a : arr)
                cout << a << " ";
            cout << endl;
        }
        break;
        case 2:
        {
            int c_array[cM][cN];
            array<array<int, cM>, cN> stl_array;
            cout << "Нажмите Y чтобы заполнить матрицу из файла" << endl;
            char choise;
            cin >> choise;
            int found = -1;
            if (tolower(choise) == 'y')
            {
                cout << "Введите имя файла" << endl;
                string filename;
                cin >> filename;
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    if (!fill_from_file(stl_array, cM, cN, filename))
                    {
                        cout << "Не удалось считать данные из файла, возможно их недостаточно или файл не существует" << endl;
                        return -1;
                    }
                    print_any_matrix(stl_array, cM, cN);

                    found = find_first_repeting_column(stl_array, cM, cN);
                }
                else
                {
                    if (!fill_from_file(c_array, cM, cN, filename))
                    {
                        cout << "Не удалось считать данные из файла, возможно их недостаточно или файл не существует" << endl;
                        return -1;
                    }
                    print_any_matrix(c_array, cM, cN);
                    found = find_first_repeting_column(c_array, cM, cN);
                }
            }
            else
            {
                cout << "Введите границы рандома" << endl;
                int a, b;
                a = read<int>(all);
                b = read<int>(greather, a);

                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    fill_from_random(stl_array, cM, cN, a, b);
                    print_any_matrix(stl_array, cM, cN);
                    found = find_first_repeting_column(stl_array, cM, cN);
                }
                else
                {
                    fill_from_random(c_array, cM, cN, a, b);
                    print_any_matrix(c_array, cM, cN);
                    found = find_first_repeting_column(c_array, cM, cN);
                }
            }
            cout << "Результат:" << found + 1 << endl;
        }
        break;
        case 3:
        {
            size_t M,N;
            array<array<int, cN>, cM> stl_array;
            vector<vector<int>> stl_vector;
            
            cout << "Нажмите Y чтобы заполнить матрицу из файла" << endl;
            char choise;
            cin >> choise;
            if (tolower(choise) == 'y')
            {
                cout << "Введите имя файла" << endl;
                string filename;
                cin >> filename;
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    fill_from_file(stl_array, cM, cN, filename);
                    print_any_matrix(stl_array, cM, cN);
                    replace_below_seconady_with_squares(stl_array, cM);
                    rotate(stl_array.begin(), stl_array.begin() + 1, stl_array.end());
                    cout << "Результат:" << endl;
                    print_any_matrix(stl_array, cM, cN);
                }
                else
                {
                    enterMN(M,N);
                    choise = 0;
                    cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                    cin >> choise;
                    if (tolower(choise) == 'y')
                    {
                        int **c_array = new int *[M];
                        for (int i = 0; i < M; i++)
                            c_array[i] = new int[N];
                        fill_from_file(c_array, M, N, filename);
                        print_any_matrix(c_array, M, N);
                        replace_below_seconady_with_squares(c_array, M);
                        rotate(c_array, c_array + 1, c_array + M);
                        cout << "Результат:" << endl;
                        print_any_matrix(c_array, M, N);
                        for (int i = 0; i < M; i++)
                            delete[] c_array[i];
                        delete[] c_array;
                    }
                    else
                    {
                        stl_vector.assign(M, vector<int>(N));
                        fill_from_file(stl_vector, M, N, filename);
                        print_any_matrix(stl_vector, M, N);
                        replace_below_seconady_with_squares(stl_vector, M);
                        rotate(stl_vector.begin(), stl_vector.begin() + 1, stl_vector.end());
                        cout << "Результат:" << endl;
                        print_any_matrix(stl_vector, M, N);
                    }
                }
            }
            else
            {
                cout << "Введите границы рандома" << endl;
                int a, b;
                a = read<int>(all);
                b = read<int>(greather, a);

                cout << "Нажмите Y чтобы использовать массив stl" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    fill_from_random(stl_array, cM, cN, a, b);
                    print_any_matrix(stl_array, cM, cN);
                    replace_below_seconady_with_squares(stl_array, cM);
                    rotate(stl_array.begin(), stl_array.begin() + 1, stl_array.end());
                    cout << "Результат:" << endl;
                    print_any_matrix(stl_array, cM, cN);
                }
                else
                {
                    enterMN(M,N);
                    choise = 0;
                    cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                    cin >> choise;
                    if (tolower(choise) == 'y')
                    {
                        int **c_array = new int *[M];
                        for (int i = 0; i < M; i++)
                            c_array[i] = new int[N];
                        fill_from_random(c_array, M, N, a, b);
                        print_any_matrix(c_array, M, N);
                        replace_below_seconady_with_squares(c_array, M);
                        rotate(c_array, c_array + 1, c_array + M);
                        cout << "Результат:" << endl;
                        print_any_matrix(c_array, M, N);
                        for (int i = 0; i < M; i++)
                            delete[] c_array[i];
                        delete[] c_array;
                    }
                    else
                    {
                        stl_vector.assign(M, vector<int>(N));
                        fill_from_random(stl_vector, M, N, a, b);
                        print_any_matrix(stl_vector, M, N);
                        replace_below_seconady_with_squares(stl_vector, M);
                        rotate(stl_vector.begin(), stl_vector.begin() + 1, stl_vector.end());
                        cout << "Результат:" << endl;
                        print_any_matrix(stl_vector, M, N);
                    }
                }
            }
        }
        break;
        case 4:
        {
            size_t M,N;
            enterMN(M,N);
            vector<vector<int>> stl_vector;
            stl_vector.assign(M, vector<int>(N));
            cout << "Нажмите Y чтобы заполнить матрицу из файла" << endl;
            char choise;
            cin >> choise;
            if (tolower(choise) == 'y')
            {
                cout << "Введите имя файла" << endl;
                string filename;
                cin >> filename;
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    int **c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        c_array[i] = new int[N];
                    fill_from_file(c_array, M, N, filename);
                    print_any_matrix(c_array, M, N);

                    int c_count = N + get_situbale_colum_count4(c_array, M, N);

                    int **new_c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        new_c_array[i] = new int[c_count];

                    insert_situable_columns4(c_array, new_c_array, M, N);

                    for (int i = 0; i < M; i++)
                    {
                        delete[] c_array[i];
                        c_array[i] = new int[c_count];
                        copy(new_c_array[i], new_c_array[i] + c_count, c_array[i]);
                        delete[] new_c_array[i];
                    }
                    delete[] new_c_array;

                    int r_count = M + get_situbale_row_count4(c_array, M, c_count);
                    new_c_array = new int *[r_count];
                    for (int i = 0; i < r_count; i++)
                        new_c_array[i] = new int[c_count];

                    insert_situable_rows4(c_array, new_c_array, M, c_count);

                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;

                    c_array = new int *[r_count];
                    for (int i = 0; i < r_count; i++)
                    {
                        c_array[i] = new int[c_count];
                        for (int j = 0; j < c_count; j++)
                            c_array[i][j] = new_c_array[i][j];
                        delete[] new_c_array[i];
                    }
                    delete[] new_c_array;

                    cout << "Результат:" << endl;
                    print_any_matrix(c_array, r_count, c_count);

                    for (int i = 0; i < r_count; i++)
                        delete[] c_array[i];
                    delete c_array;
                }
                else
                {

                    fill_from_file(stl_vector, M, N, filename);
                    print_any_matrix(stl_vector, M, N);
                    for (size_t j = 0; j < stl_vector[0].size(); j++)
                    {
                        bool situable = true;
                        for (size_t i = 0; i < M; i++)
                            if (stl_vector[i][j] < 0)
                                situable = false;
                        if (situable)
                        {
                            for (size_t i = 0; i < M; i++)
                                stl_vector[i].insert(stl_vector[i].begin() + j, (stl_vector[i].end() - 1)[0]);
                            j++;
                        }
                    }

                    cout << "Введите номер строки." << endl;
                    vector<int> choise = stl_vector[read<int>(lower, stl_vector.size())];
                    for (int i = 0; i < stl_vector.size(); i++)
                    {
                        if (all_of(stl_vector[i].begin(), stl_vector[i].end(), [](int v) { return v < 0; }))
                        {
                            stl_vector.insert(stl_vector.begin() + i, choise);
                            i++;
                        }
                    }

                    cout << "Результат:" << endl;
                    print_any_matrix(stl_vector, stl_vector.size(), stl_vector[0].size());
                }
            }
            else
            {
                cout << "Введите границы рандома" << endl;
                int a, b;
                a = read<int>(all);
                b = read<int>(greather, a);
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    int **c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        c_array[i] = new int[N];
                    fill_from_random(c_array, M, N, a, b);
                    print_any_matrix(c_array, M, N);

                    int c_count = N + get_situbale_colum_count4(c_array, M, N);

                    int **new_c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        new_c_array[i] = new int[c_count];

                    insert_situable_columns4(c_array, new_c_array, M, N);

                    for (int i = 0; i < M; i++)
                    {
                        delete[] c_array[i];
                        c_array[i] = new int[c_count];
                        copy(new_c_array[i], new_c_array[i] + c_count, c_array[i]);
                        delete[] new_c_array[i];
                    }
                    delete[] new_c_array;

                    int r_count = M + get_situbale_row_count4(c_array, M, c_count);
                    new_c_array = new int *[r_count];
                    for (int i = 0; i < r_count; i++)
                        new_c_array[i] = new int[c_count];

                    insert_situable_rows4(c_array, new_c_array, M, c_count);

                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;

                    c_array = new int *[r_count];
                    for (int i = 0; i < r_count; i++)
                    {
                        c_array[i] = new int[c_count];
                        for (int j = 0; j < c_count; j++)
                            c_array[i][j] = new_c_array[i][j];
                        delete[] new_c_array[i];
                    }
                    delete[] new_c_array;

                    cout << "Результат:" << endl;
                    print_any_matrix(c_array, r_count, c_count);

                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;
                }
                else
                {
                    fill_from_random(stl_vector, M, N, a, b);
                    print_any_matrix(stl_vector, M, N);

                    for (size_t j = 0; j < stl_vector[0].size(); j++)
                    {
                        bool situable = true;
                        for (size_t i = 0; i < M; i++)
                            if (stl_vector[i][j] < 0)
                                situable = false;
                        if (situable)
                        {
                            for (size_t i = 0; i < M; i++)
                                stl_vector[i].insert(stl_vector[i].begin() + j, (stl_vector[i].end() - 1)[0]);
                            j++;
                        }
                    }

                    cout << "Введите номер строки." << endl;
                    vector<int> choise = stl_vector[read<int>(lower, stl_vector.size())];
                    for (int i = 0; i < stl_vector.size(); i++)
                    {
                        if (all_of(stl_vector[i].begin(), stl_vector[i].end(), [](int v) { return v < 0; }))
                        {
                            stl_vector.insert(stl_vector.begin() + i, choise);
                            i++;
                        }
                    }

                    cout << "Результат:" << endl;
                    print_any_matrix(stl_vector, stl_vector.size(), stl_vector[0].size());
                }
            }
        }
        break;
        case 5:
        {
            size_t M,N;
            enterMN(M,N);
            vector<vector<int>> stl_vector;
            stl_vector.assign(M, vector<int>(N));
            cout << "Нажмите Y чтобы заполнить матрицу из файла" << endl;
            char choise;
            cin >> choise;
            if (tolower(choise) == 'y')
            {
                cout << "Введите имя файла" << endl;
                string filename;
                cin >> filename;
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    int **c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        c_array[i] = new int[N];
                    fill_from_file(c_array, M, N, filename);
                    print_any_matrix(c_array, M, N);

                    int new_row_count = M - get_situbale_row_count5(c_array,M,N);
                    int** new_c_array = new int*[new_row_count];
                    for(int i = 0;i < new_row_count;i++)
                        new_c_array[i] = new int[N];
                    remove_situable_rows5(c_array,new_c_array,M,N);

                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;

                    c_array = new int *[new_row_count];
                    for (int i = 0; i < new_row_count; i++)
                    {
                        c_array[i] = new int[N];
                        copy(new_c_array[i],new_c_array[i] + N,c_array[i]);
                        delete [] new_c_array[i];
                    }
                    
                    int new_col_count = N - get_situbale_colum_count5(c_array,new_row_count,N);
                    for(int i = 0;i < new_row_count;i++)
                        new_c_array[i] = new int[new_col_count];
                    remove_situable_columns5(c_array,new_c_array,new_row_count,N);

                    for (int i = 0; i < new_row_count; i++)
                    {
                        delete[] c_array[i];
                        c_array[i] = new int[new_col_count];
                        copy(new_c_array[i],new_c_array[i] + new_col_count,c_array[i]);
                        delete [] new_c_array[i];
                    }

                    cout << "Результат:" << endl;
                    print_any_matrix(c_array, new_row_count, new_col_count);
                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;
                }
                else
                {
                    fill_from_file(stl_vector, M, N, filename);
                    print_any_matrix(stl_vector, M, N);
                    int min = findMin(stl_vector,M,N);
                    for (size_t i = 0; i < stl_vector.size(); i++)
                    {
                        
                        if( find(stl_vector[i].begin(),stl_vector[i].end(),min) != stl_vector[i].end())
                        {
                            stl_vector.erase(stl_vector.begin()+i);
                        }
                    }

                    int max = findMax(stl_vector,stl_vector.size(),N);
                    for (size_t j = 0; j < stl_vector[0].size(); j++)
                    {
                        bool contains = false;
                        for (size_t i = 0; i < stl_vector.size(); i++)
                        {
                            if(stl_vector[i][j] == max)
                            {
                                contains = true;
                                break;
                            }
                        }
                        if(contains)
                        {
                            for (size_t i = 0; i < stl_vector.size(); i++)
                            {
                                stl_vector[i].erase(stl_vector[i].begin() + j);
                            }
                        }
                    }

                    cout << "Результат:" << endl;
                    print_any_matrix(stl_vector, stl_vector.size(), stl_vector[0].size());
                }
            }
            else
            {
                cout << "Введите границы рандома" << endl;
                int a, b;
                a = read<int>(all);
                b = read<int>(greather, a);
                choise = 0;
                cout << "Нажмите Y чтобы использовать массив ссылок" << endl;
                cin >> choise;
                if (tolower(choise) == 'y')
                {
                    int **c_array = new int *[M];
                    for (int i = 0; i < M; i++)
                        c_array[i] = new int[N];
                    fill_from_random(c_array, M, N, a, b);
                    print_any_matrix(c_array, M, N);

                    cout << "Результат:" << endl;
                    print_any_matrix(c_array, M, N);
                    for (int i = 0; i < M; i++)
                        delete[] c_array[i];
                    delete[] c_array;
                }
                else
                {
                    fill_from_random(stl_vector, M, N, a, b);
                    print_any_matrix(stl_vector, M, N);

                    cout << "Результат:" << endl;
                    print_any_matrix(stl_vector, M, N);
                }
            }
        }
        break;
        }
    }
}