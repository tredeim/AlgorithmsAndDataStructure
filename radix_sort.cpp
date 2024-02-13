#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

unsigned char getByte(unsigned int val, int i) { return (val >> (8 * i)) & 255u; }

union number
{
    unsigned int num;
    //char - 8 битовый => num будет представлен в set 4 разрядами в 256-СС
    unsigned char set[4];
};


// Функция цифровой сортировки
void radixSort(int *numbers, int array_size)
{
    number *count = new number[array_size];
    for (int i = 0; i < array_size; i++)
        count[i].num = (unsigned int)numbers[i];
    for (int digit = 0; digit < 4; digit++)
    {
        int *numeral = new int[256];
        for (int i = 0; i < 256; i++)
            numeral[i] = 0;
        for (int i = 0; i < array_size; i++)
            ++numeral[count[i].set[digit]];

        for (int i = 1; i < 256; ++i)
        {
            numeral[i] += numeral[i - 1];
        }
        for (int i = array_size - 1; i >= 0; --i)
        {
            --numeral[count[i].set[digit]];
            numbers[numeral[count[i].set[digit]]] = count[i].num;
        }
        for (int i = 0; i < array_size; ++i)
            count[i].num = (unsigned int)numbers[i];
        delete[] numeral;
    }
    for (int i = 0; i < array_size; ++i)
        numbers[i] = count[i].num;
    delete [] count;
}
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
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
