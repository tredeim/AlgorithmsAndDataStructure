#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод
//о алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer(string& s, string& t)
{
    if(s.length()> t.length())
        return Wagner_Fischer(t, s);
    int len_s = s.length();
    int len_t = t.length();
    int* lev_dist = new int[len_s + 1];
    for (int i = 0; i <= len_s; ++i)
        lev_dist[i] = i;
    for(int i = 0; i < len_t; ++i)
    {
        int prev_diagonal = lev_dist[0];
        ++lev_dist[0];
        int temp;
        for (int j = 0; j < len_s; ++j)
        {
            temp = lev_dist[j + 1];
            if (s[j] == t[i])
                lev_dist[j + 1] = prev_diagonal;
            else
                lev_dist[j + 1] = std::min(std::min(lev_dist[j], lev_dist[j + 1]), prev_diagonal) + 1;
            prev_diagonal = temp;
        }
    }
    int res = lev_dist[len_s];
    delete[] lev_dist;
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
            fout << Wagner_Fischer(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}