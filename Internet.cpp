#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

const int N = 31;


//Решает жадным методом, много раз пробовал написать нормальную динамику, но все равно все скатывалось в жадник, сорян
//long long вместо вашего int получился, когда пробовал динамику, оставил так.
long long countMinSum(long long seconds, vector<long long>& values)
{
    for (int i = 1; i < values.size(); ++i)
        if (values[i] < 2 * values[i - 1])
            values[i] = 2 * values[i - 1];
    long long price = 0;
    for (int i = N - 1; i >= 0; --i)
        if (seconds >= values[i])
        {
            seconds -= values[i];
            price += ((long long) 1) << i;
        }
    if (seconds > 0)
        ++price;
    return price;
}

int main()
{
    vector<long long> values;
    long long value = 0, seconds = 0;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> seconds;
        for (int i = 0; i < N; i++)
        {
            fin >> value;
            values.push_back(value);
        }
        fin.close();
    }

    int res = countMinSum(seconds, values);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}