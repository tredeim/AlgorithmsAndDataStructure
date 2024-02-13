#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N, int k, int m)
{
    vector<int> permutation(m + 1);
    int i = 1;
    for (i = 1; i <= m; ++i)
        permutation[i] = i;
    for (int p = 1; p < k; ++p)
    {
        for (i = m; i >= 1; --i)
            if (permutation[i] < N)
                break;
        ++permutation[i];
        for (int j = i + 1; j <= m; ++j)
            permutation[j] = permutation[j - 1] + 1;
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