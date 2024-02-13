#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

// Сортит сегмент arr с l до r (для рекурсии)
void sort_segment(int *arr, int l, int r)
{
    int i = l;
    int j = r;
    //выбираем последний элемент
    int x = arr[r];
    while (i < j)
    {
        while (arr[i] < x)
            ++i;
        while (arr[j] > x)
            --j;
        if (i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            ++i;
            --j;
        }
    }
    if (i < r)
        sort_segment(arr, i, r);
    if (j > l)
        sort_segment(arr, l, j);
}

//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
void quickSort(int *numbers, int array_size)
{
    sort_segment(numbers, 0, array_size - 1);
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    quickSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}