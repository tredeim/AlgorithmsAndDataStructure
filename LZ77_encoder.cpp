#include <fstream>
#include <vector>
#include <iostream>

const int dict_length = 3072;
const int buff_length = 1024;

class Node
{
public:
    int pos;
    int len;
    char symbol;
public:
    Node(int position, int length, char symb)
    {
        pos = position;
        len = length;
        symbol = symb;
    }
};

Node* find(std::string s, int buff_start)
{
    int buff_end = std::min(buff_start + buff_length, (int) s.size() - 1);
    int start = std::max(0, buff_start - dict_length);
    int len_max = 0, index_max = 0;
    for(int i = start; i < buff_start; ++i)
    {
        int i_temp = i, k_temp = 0;
        while(buff_start + k_temp < buff_end && s[i_temp] == s[buff_start + k_temp])
        {
            ++i_temp;
            ++k_temp;
        }
        if (i_temp - i > len_max)
        {
            len_max = i_temp - i;
            index_max = i;
        }
    }
    if(len_max == 0)
        index_max = buff_start;
    return new Node(buff_start - index_max, len_max, s[buff_start + len_max]);
}

void encode_lz77(std::string s, std::vector<Node*>& ans)
{
    int index = 0;
    Node* temp;
    while (index < s.size())
    {
        temp = find(s, index);
        ans.push_back(temp);
        index += temp->len + 1;
    }
}

int main()
{
    std::fstream fin;
    std::fstream fout;
    fin.open("input.txt", std::ios::in);
    if (fin.is_open())
    {
        std::string s;
        fin >> s;
        fin.close();
        std::vector<Node*> ans;
        encode_lz77(s, ans);
        fout.open("output.txt", std::ios::out);
        fout << ans.size() << std::endl;
        for (int i = 0; i < ans.size(); ++i)
            fout << ans[i]->pos << " " << ans[i]->len << " " << ans[i]->symbol << " ";
    }
    return 0;
}