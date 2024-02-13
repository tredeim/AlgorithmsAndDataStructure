#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

string getLCS(string x, string y)
{
    vector<vector<int>> l(x.length() + 1, vector<int>(y.length() + 1, 0));
    for (int i = 1; i <= x.length(); ++i)
        for (int j = 1; j <= y.length(); ++j)
        {
            if (x[i - 1] == y[j - 1])
            {
                l[i][j] = l[i - 1][j - 1] + 1;
            }
            else
                l[i][j] = max(l[i - 1][j], l[i][j - 1]);
        }
    string res = "";
    for (int i = x.size(), j = y.size(); i > 0 && j > 0; )
    {
        if (x[i - 1] == y[j - 1])
        {
            res = x[i - 1] + res;
            --i;
            --j;
        }
        else
            if (l[i][j] == l[i - 1][j])
                --i;
            else
                --j;
    }
    return res;
}

int main()
{
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}