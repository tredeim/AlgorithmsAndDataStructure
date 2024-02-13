#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

void quicksort_ski(Ski* skis, Student* students, int n, int l, int r);

void quicksort_students(Student* students, Ski* skis, Ski& index_ski_pivot, int n, int l, int r);

//Можно создавать любое количество любых вспомогательных методов для решения задачи.
//Рекомендуется использовать имеющиеся классы Student и Ski для решения задачи.

void quicksort_students(Student* students, Ski* skis, Ski& index_ski_pivot, int n, int l, int r)
{
    int i = l;
    int j = r;
    int index_student_pivot = -1;
    Student tempStudent;

    while (i <= j)
    {
        while (compare(students[i], index_ski_pivot) == 1)
            ++i;
        while (compare(students[j], index_ski_pivot) == -1)
            --j;

        if (compare(students[i], index_ski_pivot) == 0)
            index_student_pivot = i;
        if (compare(students[j], index_ski_pivot) == 0)
            index_student_pivot = j;

        if (i <= j)
        {
            if (index_student_pivot == i)
                index_student_pivot = j;
            else if (index_student_pivot == j)
                index_student_pivot = i;
            tempStudent = students[i];
            students[i] = students[j];
            students[j] = tempStudent;
            ++i;
            --j;
        }
    }
    if (index_student_pivot <= j)
    {
        tempStudent = students[index_student_pivot];
        students[index_student_pivot] = students[j];
        students[j] = tempStudent;
        --j;
    } else if (index_student_pivot >= i)
    {
        tempStudent = students[index_student_pivot];
        students[index_student_pivot] = students[i];
        students[i] = tempStudent;
        ++i;
    }


    if (l < j)
        quicksort_ski(skis, students, n, l, j);
    if (i < r)
        quicksort_ski(skis, students, n, i, r);
}

void quicksort_ski(Ski* skis, Student* students, int n, int l, int r)
{
    Student& student_pivot = students[l];
    int index_ski_pivot = -1;
    int i = l;
    int j = r;
    Ski tempSki;

    while (i <= j)
    {
        while (compare(student_pivot, skis[i]) == -1)
            ++i;
        while (compare(student_pivot, skis[j]) == 1)
            --j;

        if (compare(student_pivot, skis[i]) == 0)
            index_ski_pivot = i;
        if (compare(student_pivot, skis[j]) == 0)
            index_ski_pivot = j;

        if (i <= j)
        {
            if (index_ski_pivot == i)
                index_ski_pivot = j;
            else if (index_ski_pivot == j)
                index_ski_pivot = i;
            tempSki = skis[i];
            skis[i] = skis[j];
            skis[j] = tempSki;
            ++i;
            --j;
        }
    }

    if (index_ski_pivot <= j)
    {
        tempSki = skis[index_ski_pivot];
        skis[index_ski_pivot] = skis[j];
        skis[j] = tempSki;
        index_ski_pivot = j;
    } else if (index_ski_pivot >= i)
    {
        tempSki = skis[index_ski_pivot];
        skis[index_ski_pivot] = skis[i];
        skis[i] = tempSki;
        index_ski_pivot = i;
    }

    quicksort_students(students, skis, skis[index_ski_pivot], n, l, r);
}

void distribute_ski(Student* students, Student* temp_students, Ski* skis, Ski* temp_skis, int n)
{
    for (int i = 0; i < n; ++i)
    {
        students[temp_students[i].id - 1] = temp_students[i];
        skis[temp_students[i].id - 1] = temp_skis[i];
    }
}

//Задача - реализовать этот метод.
//Ответ должен быть упорядочен по возрастанию номеров студентов(!), то есть их id.
//Ответы должны быть в этих же массивах.
void findPairs(Student* students, Ski* skis, int n)
{
    Student* temp_students = new Student[n];
    Ski* temp_skis = new Ski[n];
    for (int i = 0; i < n; ++i)
    {
        temp_students[i] = students[i];
        temp_skis[i] = skis[i];
    }
    quicksort_ski(temp_skis, temp_students, n, 0, n - 1);
    distribute_ski(students, temp_students, skis, temp_skis, n);
    delete[] temp_students;
    delete[] temp_skis;
}

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}