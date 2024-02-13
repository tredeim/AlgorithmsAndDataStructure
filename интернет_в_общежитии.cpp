#include <cstdio>
#include <vector>
#include <set>
#include <queue>

const int INF = 1e9 + 2;

//1. Комнаты = вершины
//2.добавляем фиктивную вершину, расстояние от которой до i-ой комнаты равно a[i] соотв.
//3. b[i] - расстояние между комнатами, получается связный неориентированный граф
//4. строим его МОД
//5. ???
//6. PROFIT!!!
long long solve(std::vector<int>& a, std::vector<int>& b, int n)
{
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (int i = 1; i < n; ++i)
    {
        g[0].push_back({i, a[i]});
        g[i].push_back({0, a[i]});
        g[i].push_back({i + 1, b[i]});
        g[i + 1].push_back({i, b[i]});
    }
    g[0].push_back({n, a[n]});
    g[n].push_back({0, a[n]});
    ++n;
    long long ans = 0;
    std::vector<bool> used(n, false);
    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>, std::greater<>> q;
    q.push({0, 0});

    while (!q.empty())
    {
        std::pair<int, int> c = q.top();
        q.pop();
        int dst = c.first, v = c.second;
        if (!used[v])
        {
            used[v] = true;
            ans += dst;

            for (std::pair<int, int> el: g[v])
                if (!used[el.first])
                    q.push({el.second, el.first});
        }
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    std::vector<int> a(n + 1);
    std::vector<int> b(n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i)
        scanf("%d", &b[i]);

    printf("%ld", solve(a, b, n));
    return 0;
}