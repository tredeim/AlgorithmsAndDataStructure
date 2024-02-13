#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

int main()
{
    int N;
    scanf("%d", &N);
    std::vector<std::vector<int>> g(N);
    std::vector<int> degree(N, 0);

    int begin;
    int end;
    for (int i = 0; i < N - 1; ++i)
    {
        scanf("%d %d", &begin, &end);
        g[begin - 1].push_back(end - 1);
        g[end - 1].push_back(begin - 1);
    }

    std::queue<int> q;

    for (int i = 0; i < N; ++i)
    {
        degree[i] = g[i].size();
        if (degree[i] == 1)
            q.push(i);
    }

    std::vector<int> level(N, 0);
    int maxLevel = 0;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (const int i : g[v])
        {
            --degree[i];

            if (degree[i] == 1)
            {
                q.push(i);
                level[i] = level[v] + 1;
                maxLevel = std::max(maxLevel, level[i]);
            }
        }
    }

    std::vector<int> ans;
    for (int i = 0; i < N; ++i)
        if (level[i] == maxLevel)
            ans.push_back(i);
    printf("%d\n", ans.size());
    for (const int a : ans)
        printf("%d ", a + 1);
}