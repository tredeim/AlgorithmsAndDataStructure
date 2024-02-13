#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//Основная задача - реализовать данный метод
//Результат поместить в переменную res, она как раз доступна для изменения
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getBorders(string &s, string& res) 
{
    string prefix = "";
    string suffix = "";
    res = "";
    int len = s.length();
	for (int i = 0; i < len - 1; ++i)
    {
	    prefix += s[i];
        suffix = s[len - i - 1] + suffix;
        if (prefix == suffix)
            res += prefix + "\n";
    }
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
	string input;
	string res;

	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		getline(fin, input);
		fin.close();
	}

	getBorders(input, res);

	fstream fout;
	fout.open("output.txt", ios::out);
	fout << res;
	fout.close();

	return 0;
}
