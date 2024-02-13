#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string& riverMap)
{
    int prev0 = 0, prev1 = 1;
    int curr0 = 0, curr1 = 1;
    for (int i = 0; i < riverMap.length(); ++i)
    {
        switch(riverMap[i])
        {
            case 'L':
                curr0 = prev0 + 1;
                curr1 = prev1;
                break;
            case 'R':
                curr0 = prev0;
                curr1 = prev1 + 1;
                break;
            case 'B':
                curr0 = prev0 + 1;
                curr1 = prev1 + 1;
                break;
            default:
                curr0 = prev0;
                curr1 = prev1;
        }
        if (curr0 > curr1 + 1)
            curr0 = curr1 + 1;
        if (curr1 > curr0 + 0)
            curr1 = curr0 + 1;
        prev0 = curr0;
        prev1 = curr1;
    }
    return curr1;
}


int main()
{
    string riverMap;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, riverMap);
        fin.close();
    }

    res = countMaxCross(riverMap);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}