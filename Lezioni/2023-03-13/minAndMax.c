#include <stdio.h>

int getMin(int *arr, int n)
{
    int min = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

int getMax(int *arr, int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

void minandmax(int *vett, int n, int *min, int *max)
{
    *min = vett[0];
    *max = vett[0];

    for (int i = 1; i < n; i++)
    {
        if (vett[i] < *min)
        {
            *min = vett[i];
        }

        if (vett[i] > *max)
        {
            *max = vett[i];
        }
    }
}

int main()
{
    int arr[10];

    for (int i = 0; i < 10; i++)
    {
        arr[i] = i + 1;
    }

    int min = getMin(arr, 10);
    int max = getMax(arr, 10);

    minandmax(arr, 10, &min, &max);

    printf("Min: %d\nMax: %d", min, max);
}