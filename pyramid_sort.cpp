#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

void sift(int *array, int root, int heap_size)
{
    int max = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < heap_size && array[l] > array[max])
        max = l;
    if (r < heap_size && array[r] > array[max])
        max = r;
    if (max != root)
    {
        swap(array[root], array[max]);
        sift(array, max, heap_size);
    }
}

//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapSort(int *numbers, int array_size)
{
    for (int i = array_size / 2 - 1; i >= 0; --i)
        sift(numbers, i, array_size);

    for (int i = array_size - 1; i >= 1; --i)
    {
        swap(numbers[0], numbers[i]);
        --array_size;
        sift(numbers, 0, array_size);
    }
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
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}