#include <iostream>
#include <string>
#include <vector>

int findRightMost(std::vector<int>& a)
{
    int i;
    for (i = a.size() - 2; i > 0; --i)
        if (a[i] < a[i - 1])
            break;
    return i;
}

void solve(int n, std::string& res)
{
    res = "";
    std::vector<int> a(n, 1);
    for (int i = 0; i < n - 1; ++i)
        res += "1 ";
    res += "1\n";

    int rightMost;
    int sum;
    while (a.size() > 1)
    {
        rightMost = findRightMost(a);
        ++a[rightMost];
        sum = 0;
        ++rightMost;
        while(a.size() > rightMost)
        {
            sum += a.back();
            a.pop_back();
        }
        for (int i = 0; i < sum - 1; ++i)
            a.push_back(1);

        for (int i = 0; i < a.size() - 1; ++i)
            res += std::to_string(a[i]) + ' ';
        res += std::to_string(a[a.size() - 1]) + '\n';
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::string s;
    solve(n, s);
    std::cout << s;
}