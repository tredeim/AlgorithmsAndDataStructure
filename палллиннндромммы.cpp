#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void getPalindromes(string s, int* res, int n)
{
    for (int i = 0; i < n; ++i)
        res[i] = 0;
    int l = 0;
    int r = -1;
    for (int i = 0; i < n; ++i)
    {
        int k;
        if (i <= r)
            k = std::min(r - i, res[l + r - i]);
        else
            k = 1;
        while(i + k < n && i - k >= 0 && s[i - k] == s[i + k])
            ++k;
        res[i] = k;
        if (i + k - 1 > r)
        {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    for (int i = 0; i < n; ++i)
        if (res[i] > 1)
            res[i] = 2 * res[i] - 1;
}

int main()
{
    string t;
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        fin.close();
    }
    int n = t.length();
    int* res = new int[n];

    getPalindromes(t, res, n);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; ++i)
        fout << res[i] << " ";
    fout.close();

    return 0;
}
