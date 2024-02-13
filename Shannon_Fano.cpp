#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Symbol
{
public:
    Symbol(int amount)
    {
        this->amount = amount;
        code = "";
    }

    int amount;
    string code;
};

class ShannonFano
{
public:
    vector<Symbol*> symbols;

    ShannonFano()// можно изменить что бы принимал на вход количесво элементов
    {

    }

    void fano_recursive(int l, int r)
    {
        if (l >= r)
            return;
        int m = find_med(l, r);
        for (int i = l; i <= m; ++i)
            symbols[i]->code += "0";
        for (int i = m + 1; i <= r; ++i)
            symbols[i]->code += "1";
        fano_recursive(l, m);
        fano_recursive(m + 1, r);
    }

    int find_med(int l, int r)
    {
        int sum_from_left = 0;
        for (int i = l; i < r; ++i)
            sum_from_left += symbols[i]->amount;
        int sum_from_right = symbols[r]->amount;
        int m = r;
        int d;
        do
        {
            d = sum_from_left - sum_from_right;
            --m;
            sum_from_left -= symbols[m]->amount;
            sum_from_right += symbols[m]->amount;
        } while (abs(sum_from_left - sum_from_right) <= d);
        return m;
    }

    void build()
    {
        fano_recursive(0, symbols.size() - 1);
    }

    void addChance(int chance)
    {
        symbols.push_back(new Symbol(chance));
    }

    string get(int i)
    {
        return symbols[i]->code;
    }

};


int main()
{

    int n;
    ShannonFano* shf = new ShannonFano();

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            shf->addChance(x);
        }

        fin.close();

        shf->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << shf->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete shf;

    }
    return 0;
}