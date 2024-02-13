#include <fstream>
#include <string>
#include <vector>

void gen_next(std::vector<int>& positions, int n)
{
    int i = positions.size() - 1;
    for (i; i > 0; --i)
    {
        if (positions[i] != positions[i - 1] + 1)
        {
            --positions[i];
            break;
        }
    }
    if (i == 0 && positions[0] > 0)
    {
        --positions[0];
    }
    for (int j = i + 1; j < positions.size(); ++j)
        positions[j] = n - positions.size() + j;
}

void solve(int n, int m, int k, std::string& res)
{
    std::vector<int> pieces(m - 1);
    for (int i = 0; i < m - 1; ++i)
        pieces[i] = n + i;
    for (int i = 1; i < k; ++i)
    {
        gen_next(pieces, n + m - 1);
    }

    res = std::to_string(pieces[0]) + ' ';
    for (int i = 1; i < pieces.size(); ++i)
        res += std::to_string(pieces[i] - pieces[i - 1] - 1) + ' ';
    res += std::to_string(n + m - 2 - pieces[pieces.size() - 1]);
}

int main()
{
    int M, N, K;
    std::fstream fin;
    std::fstream fout;
    fin.open("input.txt", std::ios::in);
    fout.open("output.txt", std::ios::out);
    if (fin.is_open())
    {
        std::string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        std::string ans;
        solve(N, M, K, ans);
        fout << ans;
        fout.close();
        fin.close();
    }
    return 0;
}