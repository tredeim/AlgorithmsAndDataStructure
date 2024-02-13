#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool sortComponentsByName(vector<string> c1, vector<string> c2)
{
    return c1[0] < c2[0];
}

void dfs1(const vector<vector<bool>>& r, vector<bool>& used, vector<int>& order, int n, int v)
{
    used[v] = true;
    for (int i = 0; i < n; ++i)
        if (r[v][i] && !used[i])
            dfs1(r, used, order, n, i);
    order.push_back(v);
}

void dfs2(const vector<vector<bool>>& r, vector<bool>& used, const vector<string>& names, vector<string>& component,
          int n, int v)
{
    used[v] = true;
    component.push_back(names[v]);
    for (int i = 0; i < n; ++i)
        if (r[i][v] && !used[i])
            dfs2(r, used, names, component, n, i);
}

vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations)
{
    int n = names.size();
    vector<bool> used(n, false);
    vector<vector<string>> components;
    vector<int> order;

    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs1(relations, used, order, n, i);
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
    {
        int v = order[n - i - 1];
        if (!used[v])
        {
            vector<string> component;
            dfs2(relations, used, names, component, n, v);
            components.push_back(component);

        }
    }
    for (auto & component : components)
        sort(component.begin(), component.end());
    sort(components.begin(), components.end(), sortComponentsByName);
    return components;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str = "";
        getline(fin, str);
        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }
        relations = vector<vector<bool >>(names.size());
        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }
        getline(fin, str);
        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }
        fin.close();
    }

    vector<vector<string>> res = getList(names, relations);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();
    return 0;
}