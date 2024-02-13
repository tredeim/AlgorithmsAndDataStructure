#include <fstream>
#include <stack>
#include <string>

using namespace std;

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(long long  N, long long k)
{
    stack<int> tracks;
    tracks.push((k - 1) % N + 1);
    k /= N;
    long long last = N - 1;
    while (k > 0)
    {
        tracks.push(k % last + 1);
        k /= last;
        --last;
    }

    string ans = "";
    for (long long i = 0; i < N - tracks.size(); ++i)
    {
        ans += "1 ";
    }

    int temp;
    while(!tracks.empty())
    {
        temp = tracks.top();
        tracks.pop();
        ans += to_string(temp);
        if (!tracks.empty())
            ans += " ";
    }
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
        K = stol(str.c_str());
        fout << get(N, K);

        fout.close();
        fin.close();
    }
    return 0;
}