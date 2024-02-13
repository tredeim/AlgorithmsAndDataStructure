#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод
//о алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer_for_Damerau_Levenshtein(string& s, string& t)
{
    int m = s.length() + 1;
    int n = t.length() + 1;
    int** d = new int* [m];
    for (int i = 0; i < m; ++i)
    {
        d[i] = new int[n];
        d[i][0] = i;
    }
    for (int j = 0; j < n; ++j)
        d[0][j] = j;
    for (int j = 1; j < n; ++j)
        for (int i = 1; i < m; ++i)
        {
            if (s[i - 1] == t[j - 1])
                d[i][j] = d[i - 1][j - 1];
            else if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1])
                d[i][j] = min(min(d[i][j - 1], d[i - 1][j]),
                              min(d[i - 1][j - 1], d[i - 2][j - 2])) + 1;
            else
                d[i][j] = min(d[i][j - 1], min(d[i - 1][j], d[i - 1][j - 1])) + 1;
        }
    int res = d[m - 1][n - 1];
    for (int i = 0; i < m; ++i)
        delete[] d[i];
    delete[] d;
    return res;
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main(int argc, const char* argv[])
{
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string N;
        getline(fin, N);
        n = atoi(N.c_str());
        for (int i = 0; i < n; i++)
        {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer_for_Damerau_Levenshtein(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}