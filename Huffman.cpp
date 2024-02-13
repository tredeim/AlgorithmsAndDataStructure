#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Node
{
public:
    Node* left_child;
    Node* right_child;
    int amount;
    string code;

    Node(int val)
    {
        amount = val;
        left_child = nullptr;
        right_child = nullptr;
    }

    Node(int val, Node* left, Node* right) : Node(val)
    {
        left_child = left;
        right_child = right;
    }
};

class Huffman
{
private:
    vector<Node*> leafs;

public:

    void build()
    {
        vector<Node*> current_level;

        for (int i = 0; i < leafs.size(); ++i)
            current_level.push_back(leafs[i]);

        while (current_level.size() > 1)
        {
            cout << "pizda";
            Node* right_node = current_level.back();
            current_level.pop_back();
            Node* left_node = current_level.back();
            Node* new_node = new Node(left_node->amount + right_node->amount, left_node, right_node);
            int i;
            for (i = current_level.size() - 2; i >= 0; --i)
                if (new_node->amount > current_level[i]->amount)
                    current_level[i + 1] = current_level[i];
                else
                    break;
            current_level[i + 1] = new_node;
        }
        Node* root = current_level.back();
        current_level.pop_back();
        build_code(root, "");
    }

    void build_code(Node* node, string code)
    {
        if (!node->left_child)
        {
            node->code = code;
            return;
        }
        build_code(node->left_child, code + "1");
        build_code(node->right_child, code + "0");
    }

    void addChance(int chance)
    {
        leafs.push_back(new Node(chance));
    }

    string get(int i)
    {
        return leafs[i]->code;
    }

};


int main()
{

    int n;
    Huffman* huff = new Huffman();
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            huff->addChance(x);
        }

        fin.close();

        huff->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << huff->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete huff;

    }

    return 0;

}

