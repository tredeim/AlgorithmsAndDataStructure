#include <fstream>
#include <vector>

const int dict_length = 3072;
const int window_length = 1024;

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

    Node()
    {

    }
};

std::string decode_lz77(Node* arr, int n)
{
    std::string ans = "";
    for (int i = 0; i < n; ++i)
    {
        if (arr[i].pos < arr[i].len)
            while (arr[i].len > arr[i].pos)
            {
                ans += ans.substr(ans.length() - arr[i].pos, arr[i].pos);
                arr[i].len -= arr[i].pos;
            }
        ans += ans.substr(ans.length() - arr[i].pos, arr[i].len) + arr[i].symbol;
    }
    return ans;
}

int main()
{
    std::fstream fin;
    std::fstream fout;
    fin.open("input.txt", std::ios::in);
    int n;
    fin >> n;
    Node* arr = new Node[n];
    int temp_pos;
    int temp_len;
    char temp_char;
    for (int i = 0; i < n; ++i)
    {
        fin >> temp_pos >> temp_len >> temp_char;
        arr[i] = Node(temp_pos, temp_len, temp_char);
    }
    fin.close();
    fout.open("output.txt", std::ios::out);
    fout << decode_lz77(arr, n);
    fout.close();
	delete[] arr;
    return 0;
}