#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    int* br = new int[substring.length()];
    br[0] = 0;
    int t;
    for (int i = 1; i < substring.length(); ++i)
    {
        t = br[i - 1];
        while (t > 0 && substring[i] != substring[t])
            t = br[t - 1];
        if (substring[i] == substring[t])
            br[i] = t + 1;
        else
            br[i] = 0;
    }

    int iter = 0;
    for (int i = 0; i < source.length(); ++i)
    {
        while (substring.length() - iter <= source.length() - i &&
               ((iter > 0 && source[i] != substring[iter]) || iter == substring.length()))
            iter = br[iter - 1];
        if (source[i] == substring[iter])
            ++iter;
        if (iter == substring.length())
            res.push_back(i - iter + 1);
    }
    delete[] br;
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}
