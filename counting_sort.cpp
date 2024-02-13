#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Макс число среди данных чисел
const int k = 1000000;

// Функция сортировки подсчетом
void countingSort(int *numbers, int array_size)
{
    int *count = new int[k + 1];
    int *temp_array = new int[array_size];

    for (int i = 0; i <= k; ++i)
        count[i] = 0;

    for (int i = 0; i < array_size; ++i)
        ++count[numbers[i]];

    for (int i = 1; i <= k; i++)
        count[i] += count[i - 1];
    for (int i = array_size - 1; i >= 0; --i)
    {
        --count[numbers[i]];
        temp_array[count[numbers[i]]] = numbers[i];
    }

    for (int i = 0; i < array_size; ++i)
        numbers[i] = temp_array[i];

    delete[] temp_array;
    delete[] count;
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
    countingSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);
    //освобождаем память
    delete[] brr;

    return 0;
}