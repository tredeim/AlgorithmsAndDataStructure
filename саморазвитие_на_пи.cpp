#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод используя рекурсивный подход
int LevenshteinDistance(string& s, int len_s, string& t, int len_t, int current_d, int max_d)
{
    if (len_s == 0)
        return len_t;
    if (len_t == 0)
        return len_s;
    if (s[len_s - 1] == t[len_t - 1])
        return LevenshteinDistance(s, len_s - 1, t, len_t - 1, current_d, max_d);
    else
    {
        if (++current_d > max_d)
            return current_d;
        return min(LevenshteinDistance(s, len_s - 1, t, len_t, current_d, max_d),
                   min(LevenshteinDistance(s, len_s - 1, t, len_t - 1, current_d, max_d),
                       LevenshteinDistance(s, len_s, t, len_t - 1, current_d, max_d))) + 1;
    }
}

int main(int argc, const char* argv[])
{
    int n;
    std::fstream fin;
    std::fstream fout;
    fin.open("input.txt", std::ios::in);
    if (fin.is_open())
    {
        fout.open("output.txt", std::ios::out);
        fin >> n;
        std::string* arr = new std::string[n];
        for (int i = 0; i < n; ++i)
            fin >> arr[i];
        int d;
        fin >> d;
        int k;
        fin >> k;
        std::string s;
        for (int i = 0; i < k; ++i)
        {
            int count = 0;
            fin >> s;
            for (int j = 0; j < n; ++j)
                if (LevenshteinDistance(s, s.length(), arr[j], arr[j].length(), 0, d) <= d)
                    ++count;
            fout << count << "\n";
        }
        fin.close();
        fout.close();
        delete[] arr;
    }
    return 0;
}