#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

void findAns(vector<vector<int>>& table, int i, int j, pair<int, int>* items, vector<pair<int, int>>& res)
{
    if (table[i][j] == 0)
        return;
    if (table[i - 1][j] == table[i][j])
        findAns(table, i - 1, j, items, res);
    else
    {
        findAns(table, i - 1, j - items[i - 1].first, items, res);
        res.push_back(items[i - 1]);
    }
}

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
{
    vector<vector<int>> table(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= W; ++j)
            if (j >= items[i - 1].first)
                table[i][j] = std::max(table[i - 1][j], table[i - 1][j - items[i - 1].first] + items[i - 1].second);
            else
                table[i][j] = table[i - 1][j];
    findAns(table, N, W, items, res);
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int>* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++)
    {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}