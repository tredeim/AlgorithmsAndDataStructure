#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct cloth
{
    string name;
    int index;
};

bool sortByName(const cloth& c1, const cloth& c2)
{
    return c1.name < c2.name;
}

void dfs(const vector<string>& names, const vector<vector<bool>>& r, vector<bool>& used, vector<bool>& inAns,
         vector<string>& ans, int n, int index)
{
    vector<cloth> children;
    used[index] = true;
    for (int j = 0; j < n; ++j)
        if (r[index][j] && !used[j])
            children.emplace_back(cloth{names[j], j});
    sort(children.begin(), children.end(), sortByName);
    for (cloth& i : children)
        if (!used[i.index])
            dfs(names, r, used, inAns, ans, n, i.index);
    if (!inAns[index])
    {
        ans.emplace_back(names[index]);
        inAns[index] = true;
    }
}

vector<string> getList(const vector<string>& names, const vector<vector<bool>>& relations)
{
    int n = names.size();
    vector<cloth> nodes;
    for (int j = 0; j < n; ++j)
    {
        bool is_source = true;
        for (int i = 0; i < n; ++i)
            if (relations[i][j])
            {
                is_source = false;
                break;
            }
        if (is_source)
            nodes.emplace_back(cloth{names[j], j});
    }
    sort(nodes.begin(), nodes.end(), sortByName);
    vector<bool> used(n, false);
    vector<bool> inAns(n, false);
    vector<string> ans;
    for (cloth& node : nodes)
        dfs(names, relations, used, inAns, ans, n, node.index);
    reverse(ans.begin(), ans.end());
    return ans;
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
        relations = vector<vector<bool>>(names.size());
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
    vector<string> res = getList(names, relations);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();
    return 0;
}