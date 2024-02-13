#include <fstream>
#include <vector>

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
int solve(int N, int W, pair<int, int>* items)
{
    vector<vector<int>> table(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= W; ++j)
            if (j >= items[i - 1].first)
                table[i][j] = std::max(table[i - 1][j], table[i - 1][j - items[i - 1].first] + items[i - 1].second);
            else
                table[i][j] = table[i - 1][j];
    return table[N][W];
}

int main(int argc, const char* argv[])
{
    int N;
    int W;
    std::fstream fin;
    fin.open("input.txt", std::ios::in);
    fin >> N;
    fin >> W;
    pair<int, int>* arr = new pair<int, int>[N];
    for (int i = 0; i < N; ++i)
        fin >> arr[i].first;
    for (int i = 0; i < N; ++i)
        fin >> arr[i].second;
    fin.close();

    std::fstream fout;
    fout.open("output.txt", std::ios::out);
    int res = solve(N, W, arr);
    fout << solve(N, W, arr);
    fout.close();
    delete[] arr;
    return 0;
}