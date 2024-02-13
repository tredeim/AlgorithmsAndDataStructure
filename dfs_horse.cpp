#include <algorithm>
#include "ReadWriter.cpp"

//Можно добавлять любые методы для решения задачи.
bool sortByName(Node* n1, Node* n2)
{
    return n1->name < n2->name;
}

void dfs(Node* node, std::vector<std::string>& result)
{
    if (node->visited)
        return;
    node->visited = true;
    result.push_back(node->name);
    std::sort(node->neighbours.begin(), node->neighbours.end(), sortByName);
    for (Node* neighbour : node->neighbours)
        dfs(neighbour, result);
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    dfs(&graph[start], result);
}

int main()
{
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}