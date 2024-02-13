#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get_day(int N, int k)
{
    vector<int> permutation(N + 1);
    int i = 1;
    for (i = 1; i <= N; ++i)
        permutation[i] = i;
    int min;
    for (int p = 1; p < k; ++p)
    {
        for (i = N - 1; i >= 1; --i)
            if (permutation[i] < permutation[i + 1])
                break;
        min = i;
        for (int j = i + 1; j <= N; ++j)
            if (permutation[j] > permutation[i] && (min == i || permutation[j] < permutation[min]))
                min = j;
        swap(permutation[i], permutation[min]);
        reverse(permutation.begin() + i + 1, permutation.end());
    }

    string ans = "";
    for (i = 1; i < N; ++i)
        ans += to_string(permutation[i]) + " ";
    ans += to_string(permutation[N]);
    return ans;
}

int main(int argc, const char* argv[])
{
    int N, K;
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
        fout << get_day(N, K);

        fout.close();
        fin.close();
    }

    return 0;
}