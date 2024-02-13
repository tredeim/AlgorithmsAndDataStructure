#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

using namespace std;
int const INF = 1e9;

void ReadWriter::writeValues(std::vector<std::vector<int>>& result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result.size(); i++)
        for (int j = 0; j < result.size(); j++)
            if (result[i][j] == INF)
                fout << i << ' ' << j << ' ' << -1 << '\n';
            else if (i != j)
                fout << i << ' ' << j << ' ' << result[i][j] << '\n';
}

void relax(vector<vector<int>>& l, vector<vector<int>>& w, bool& flag)
{
    for (int i = 0; i < l.size(); i++)
        for (int j = 0; j < l.size(); j++)
            if (i != j)
                for (int k = 0; k < l.size(); k++)
                {
                    if (l[i][k] + w[k][j] < l[i][j])
                    {
                        l[i][j] = l[i][k] + w[k][j];
                        flag = false;
                    }
                }
}

void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    vector<vector<int>> w;
    w = vector<vector<int>>(N, vector<int>(N, INF));
    for (int i = 0; i < N; i++)
        w[i][i] = 0;
    for (const Edge edge: edges)
        w[edge.A][edge.B] = edge.W;

    result = w;

    for (int i = 1; i < N - 1; i++)
    {
        bool flag = true;
        relax(result, w, flag);
        if (flag)
            break;
    }

}


int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}