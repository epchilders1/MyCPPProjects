#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Merge(int numbers[], int i, int j, int k)
{
    int mergedSize; // Size of merged partition
    int mergePos;   // Position to insert merged number
    int leftPos;    // Position of elements in left partition
    int rightPos;   // Position of elements in right partition
    int *mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                         // Initialize left partition position
    rightPos = j + 1;                    // Initialize right partition position
    mergedNumbers = new int[mergedSize]; // Dynamically allocates temporary array
                                         // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k)
    {
        if (numbers[leftPos] < numbers[rightPos])
        {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else
        {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j)
    {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k)
    {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}
int partition(string arr[], int low, int high)
{
    string pivot = arr[high]; // choose last element as pivot
    int i = low - 1;          // index of smaller element

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]); // put pivot at its correct position
    return i + 1;                // return the index of pivot
}
void MergeSort(int numbers[], int i, int k)
{
    int j;

    if (i < k)
    {
        j = (i + k) / 2; // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}
void quickSort(string arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        // recursively sort each side of the array
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        cout << "Invalid number of arguments" << endl;
        return 0;
    }

    else
    {
        if (*argv[1] == 'i')
        {
            ifstream intFile1;
            ifstream intFile2;
            intFile1.open(argv[2]);
            intFile2.open(argv[3]);

            int arr1Size = 0;
            int arr2Size = 0;
            int *arr1 = new int[20000];
            int *arr2 = new int[20000];
            int *matches = new int[20000];
            while (!intFile1.eof())
            {
                intFile1 >> arr1[arr1Size];
                arr1Size++;
            }
            arr1Size--;
            while (!intFile2.eof())
            {
                intFile2 >> arr2[arr2Size];
                arr2Size++;
            }
            arr2Size--;

            MergeSort(arr1, 0, arr1Size - 1);
            MergeSort(arr2, 0, arr2Size - 1);
            int matchPoint = 0;
            for (int i = 0; i < arr1Size; i++)
            {
                for (int x = 0; x < arr2Size; x++)
                {
                    if (arr1[i] == arr2[x])
                    {
                        matches[matchPoint] = arr1[i];
                        matchPoint++;
                    }
                }
            }
            for (int i = 0; i < matchPoint; i++)
            {
                if (i >= 1)
                {
                    if (matches[i] != matches[i - 1])
                    {
                        cout << matches[i] << endl;
                    }
                }
                else
                {
                    cout << matches[i] << endl;
                }
            }
        }
        if (*argv[1] == 's')
        {
            ifstream stringFile1;
            ifstream stringFile2;
            stringFile1.open(argv[2]);
            stringFile2.open(argv[3]);

            int arr1Size = 0;
            int arr2Size = 0;
            string arr1[20000];
            string arr2[20000];
            string matches[20000];
            while (!stringFile1.eof())
            {
                stringFile1 >> arr1[arr1Size];
                arr1Size++;
            }
            arr1Size--;
            while (!stringFile2.eof())
            {
                stringFile2 >> arr2[arr2Size];
                arr2Size++;
            }
            arr2Size--;
            quickSort(arr1, 0, arr1Size - 1);
            quickSort(arr2, 0, arr2Size - 1);

            int matchPoint = 0;
            for (int i = 0; i < arr1Size; i++)
            {
                for (int x = 0; x < arr2Size; x++)
                {
                    if (arr1[i] == arr2[x])
                    {
                        matches[matchPoint] = arr1[i];
                        matchPoint++;
                    }
                }
            }
            for (int i = 0; i < matchPoint; i++)
            {
                if (i >= 1)
                {
                    if (matches[i] != matches[i - 1])
                    {
                        cout << matches[i] << endl;
                    }
                }
                else
                {
                    cout << matches[i] << endl;
                }
            }
        }
    }

    return 0;
}