#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
void MergeSort::sort(int* arr, int length)
{
    divide_and_merge(arr, 0, length - 1);
}

void MergeSort::merge(int* arr, int first, int second, int end)
{
    int* b = new int[end - first + 1];
    int pos0 = 0, pos1 = first, pos2 = second + 1;
    while (pos1 <= second && pos2 <= end)
        if (arr[pos1] < arr[pos2])
            b[pos0++] = arr[pos1++];
        else
            b[pos0++] = arr[pos2++];
    while (pos2 <= end)
        b[pos0++] = arr[pos2++];
    while (pos1 <= second)
        b[pos0++] = arr[pos1++];
    for (int i = 0; i < end - first + 1; i++)
        arr[first + i] = b[i];
    delete[] b;
}

void MergeSort::divide_and_merge(int* arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        divide_and_merge(arr, left, mid);
        divide_and_merge(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    ReadWriter rw;

    int* brr = nullptr;
    int length;

    //Read data from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}
