#include <fstream>

using namespace std;

std::fstream fin;
std::fstream fout;

void readArrays(int *begin, int *end, int length) {
    if (!fin.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < length; i++)
        fin >> begin[i] >> end[i];
}

int readInt() {
    int x;
    fin >> x;
    return x;
}

void printInt(int x) {
    fout << x << "\n";
}

void merge(int *arr, int first, int second, int end) {
    int *b = new int[end - first + 1];
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

void divide_and_merge(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        divide_and_merge(arr, left, mid);
        divide_and_merge(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void sort(int *arr, int length) {
    divide_and_merge(arr, 0, length - 1);
}

int binpoisk(int* a, int request, int r)
{
    int l = 0;
    while(l < r)
    {
        int mid = l + (r - l) / 2;
        if (a[mid] <= request)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int binpoisk_left(int* a, int request, int n)
{
    int l = 0;
    int r = n;
    while(l < r)
    {
        int mid = l + (r - l) / 2;
        if (a[mid] < request)
            l = mid + 1;
        else
            r = mid;
    }
    if (l + 1 < n && a[l] < request)
        ++l;
    return l;
}

int main() {
    fin.open("input.txt", std::ios::in);
    fout.open("output.txt", std::ios::out);
    int n;
    n = readInt();
    int *begin = new int[n];
    int *end = new int[n];
    readArrays(begin, end, n);

    sort(begin, n);
    sort(end, n);

    int k = readInt();
    int request;
    for (int i = 0; i < k; ++i)
    {
        request = readInt();
        printInt(binpoisk(begin, request, n) - binpoisk_left(end, request, n));
    }

    fin.close();
    fout.close();
    delete[] begin;
    delete[] end;

    return 0;
}