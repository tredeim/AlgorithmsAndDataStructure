#include <vector>
#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;

long long countWays(int i, int j, vector<vector<long long>>& table, int N, int M)
{
    if (table[i][j] != -1)
        return table[i][j];
    table[i][j] = 0;
    if (i - 2 >= 0)
    {
        if (j - 1 >= 0)
            table[i][j] += countWays(i - 2, j - 1, table, N, M);
        if (j + 1 < M)
            table[i][j] += countWays(i - 2, j + 1, table, N, M);
    }
    if(j - 2 >= 0)
    {
        if (i - 1 >= 0)
            table[i][j] += countWays(i - 1, j - 2, table, N, M);
        if (i + 1 < N)
            table[i][j] += countWays(i + 1, j - 2, table, N, M);
    }
    return table[i][j];
}
//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    vector<vector<long long>> table(N, vector<long long>(M, -1));
    table[0][0] = 1;
    return countWays(N - 1, M - 1, table, N, M);
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}