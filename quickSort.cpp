#include "precomp.h"

int partition(vector<Tank>& original, int left, int right)
{
    int pivotIndex = left + (right - left) / 2;
    Tank pivotValue = original[pivotIndex];
    int i = left, j = right;
    Tank temp = pivotValue;
    while (i <= j)
    {
        while (original[i].health < pivotValue.health)
        {
            i++;
        }
        while (original[j].health > pivotValue.health)
        {
            j--;
        }
        if (i <= j)
        {
            temp = original[i];
            //cout << i << endl;
            original[i] = original[j];
            //original.insert(original.begin() + i, original[j]);
            original[j] = temp;
            //original.insert(original.begin() + j, temp);
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(vector<Tank>& original, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(original, left, right);
        quicksort(original, left, pivotIndex - 1);
        quicksort(original, pivotIndex, right);
    }
}
