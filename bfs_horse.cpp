#include <algorithm>
#include "ReadWriter.cpp"

//Можно добавлять любые методы для решения задачи.
bool sortByName(Node* n1, Node* n2)
{
    return n1->name < n2->name;
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    std::vector<Node*> currentLevel;
    currentLevel.push_back(&graph[start]);
    std::vector<Node*> nextLevel;
    while (!currentLevel.empty())
    {
        for (Node* node : currentLevel)
        {
            if (!node->visited)
            {
                result.push_back(node->name);
                node->visited = true;
                for (int i = 0; i < node->neighbours.size(); ++i)
                {
                    if (!node->neighbours[i]->visited)
                        nextLevel.push_back(node->neighbours[i]);
                }
            }
        }
        std::sort(nextLevel.begin(), nextLevel.end(), sortByName);
        currentLevel = nextLevel;
        nextLevel.clear();
    }
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
