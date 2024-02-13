#include <fstream>
#include <vector>

int main()
{
    int n;
    std::fstream fin;
    fin.open("input.txt", std::ios::in);
    fin >> n;
    int a;
    int b;
    int c;
    fin >> a >> b >> c;
    fin.close();
    std::vector<int> e(n + 1, 0);
    e[1] = 1;
    int count = 1;
    for (int i = std::min(a, std::min(b, c)) + 1; i <= n; ++i)
    {
        if (i - a >= 1 && e[i - a] == 1)
        {
            e[i] = 1;
            ++count;
            continue;
        }
        if (i - b >= 1 && e[i - b] == 1)
        {
            e[i] = 1;
            ++count;
            continue;
        }
        if (i - c >= 1 && e[i - c] == 1)
        {
            e[i] = 1;
            ++count;
        }
    }
    std::fstream fout;
    fout.open("output.txt", std::ios::out);
    fout << count;
    fout.close();
}