#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void findAns(vector<vector<int>>& table, int i, int j, int* stones, vector<int>& res)
{
    if (table[i][j] == 0)
        return;
    if (table[i - 1][j] == table[i][j])
        findAns(table, i - 1, j, stones, res);
    else
    {
        findAns(table, i - 1, j - stones[i - 1], stones, res);
        res.push_back(stones[i - 1]);
    }
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int* stones, vector<int>& res)
{
    vector<vector<int>> table(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= W; ++j)
            if (j >= stones[i - 1])
                table[i][j] = max(table[i - 1][j], table[i - 1][j - stones[i - 1]] + stones[i - 1]);
            else
                table[i][j] = table[i - 1][j];
    findAns(table, N, W, stones, res);
}

int main(int argc, const char* argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int* arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}