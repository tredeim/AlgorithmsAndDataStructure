#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

static bool checkNext(vector<bool>& used, int x)
{
    for (int i = x + 1; i < used.size(); ++i)
        if (!used[i])
            return true;
    return false;
}
//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N, int k, int m)
{
    vector<int> permutation(m + 1);
    vector<bool> used(N + 1, false);
    int i;
    for (i = 1; i <= m; ++i)
        used[i] = true;
    for (i = 1; i <= m; ++i)
        permutation[i] = i;
    for (int p = 1; p < k; ++p)
    {
        for (i = m; i >= 1; --i)
        {
            used[permutation[i]] = false;
            if (permutation[i] < N && checkNext(used, permutation[i]))
                break;
        }
        while(used[++permutation[i]]);
        used[permutation[i]] = true;
        int f = 1;
        for (int j = i + 1; j <= m; ++j)
        {
            while (used[f])
                ++f;
            permutation[j] = f;
            used[f] = true;
        }
    }

    string ans = "";
    for (i = 1; i < m; ++i)
        ans += to_string(permutation[i]) + " ";
    ans += to_string(permutation[m]);
    return ans;
}

int main(int argc, const char* argv[])
{
    int M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get(N, K, M);

        fout.close();
        fin.close();
    }
    return 0;
}