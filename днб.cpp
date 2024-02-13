#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

//Необходимо реализовать данный метод
static string get(long long  N, long long m, long long k)
{
    stack<int> tracks;
    if (k % N == 0)
        tracks.push(1);
    else
        tracks.push(k % N);
    k /= N;
    while (k > 0)
    {
        tracks.push(k % N + 1);
        k /= N;
    }

    string ans = "";
    for (long long i = m - 1; i >= tracks.size(); --i)
    {
        ans += "1 ";
    }

    int temp;
    for (long long i = tracks.size() - 1; i > 0; --i)
    {
        temp = tracks.top();
        tracks.pop();
        ans += to_string(temp) + " ";
    }
    temp = tracks.top();
    tracks.pop();
    ans += to_string(temp);
    return ans;
}

int main(int argc, const char* argv[])
{
    long long M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = stol(str.c_str());
        getline(fin, str);
        M = stol(str.c_str());
        getline(fin, str);
        K = stol(str.c_str());
        fout << get(N, M, K);

        fout.close();
        fin.close();
    }
    return 0;
}