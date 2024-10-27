#pragma once
#include <stdio.h>

void bubble_sort(int *array, int limit)
{
    int i, j, temp;
    for (i = 0; i < limit - 1; i++)
    {
        for (j = 0; j < limit - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void print_array(int *array, int limit)
{
    int i;
    for (i = 0; i < limit; i++)
    {
        printf("%d, ", array[i]);
    }
}

void scan_array(int *array, int limit)
{
    int i;
    for (i = 0; i < limit; i++)
    {
        printf("Enter element no. %d for array: ", i + 1);
        scanf("%d", &array[i]);
    }
}

void merge_sorted_array(int *array1, int *array2, int *merge, int limit1, int limit2) // input should be sorted arrays
{
    int i, n1, n2, merge_count = 0;

    for (i = 0, n1 = 0, n2 = 0; i < limit1 + limit2; i++)
    {
        if (n1 < limit1 && n2 < limit2)
        {
            if (array1[n1] >= array2[n2])
            {
                merge[i] = array2[n2];
                merge_count++;
                n2++;
            }
            else if (array2[n2] >= array1[n1])
            {
                merge[i] = array1[n1];
                merge_count++;
                n1++;
            }
        }
        else
        {
            if (n1 == limit1 && n2 < limit2)
            {
                merge[i] = array2[n2];
                merge_count++;
                n2++;
            }
            else if (n2 == limit2 && n1 < limit1)
            {
                merge[i] = array1[n1];
                merge_count++;
                n1++;
            }
        }
    }
}

void insertion_sort(int *array, int limit)
{
    int i = 1, j = 1, key;
    for (i = 1; i < limit; i++)
    {
        key = array[i];
        j = i - 1;
        while (j >= 0 && key < array[j])
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int minimum(int *array, int limit)
{
    int i, min;
    for (i = 0, min = array[0]; i < limit; i++)
    {
        if (min > array[i])
            min = array[i];
    }

    return min;
}

int maximum(int *array, int limit)
{
    int i, max;
    for (i = 0, max = array[0]; i < limit; i++)
    {
        if (max < array[i])
            max = array[i];
    }

    return max;
}

void print_array_2d(int **array, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d, ", array[i][j]);
        }
        printf("\n");
    }
}

void scan_array_2d(int **array, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("Enter the value in (%d, %d): ", i + 1, j + 1);
            scanf_s("%d", &array[i][j]);
        }
    }
}

int maximum_2d(int **array, int row, int col)
{
    int i, j, max;
    max = array[0][0];
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (array[i][j] > max)
            {
                max = array[i][j];
            }
        }
    }

    return max;
}

int minimum_2d(int **array, int row, int col)
{
    int i, j, min;
    min = array[0][0];
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (array[i][j] < min)
            {
                min = array[i][j];
            }
        }
    }

    return min;
}

int **malloc_2d(int **array, int row, int col)
{
    int i;
    array = (int **)malloc(row * sizeof(int *));

    for (i = 0; i < row; i++)
    {
        array[i] = (int *)malloc(col * sizeof(int));
    }

    return array;
}
