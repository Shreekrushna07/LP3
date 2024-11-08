/*
Name: Shreekrushna Ravindra Dongare
Lab: LP4
Roll No: 44
BE_COMP_A_44
*/

#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
using namespace std;

class Solution{
public:
    void quickSort_deterministic(int arr[], int low, int high)
    {
        if (low < high)
        {
            int pindex = partition(arr, low, high);
            quickSort_deterministic(arr, low, pindex - 1);
            quickSort_deterministic(arr, pindex + 1, high);
        }
    }
    void quickSort_randomized(int arr[], int low, int high)
    {
        if (low < high)
        {
            int pindex = randomizedPartition(arr, low, high);
            quickSort_randomized(arr, low, pindex - 1);
            quickSort_randomized(arr, pindex + 1, high);
        }
    }

    int randomizedPartition(int arr[], int low, int high)
    {
        int randomPivotIndex = low + rand() % (high - low + 1);
        swap(arr[low], arr[randomPivotIndex]);
        return partition(arr, low, high);
    }

    int partition(int arr[], int low, int high)
    {
        int pivot = arr[low];
        int i = low;
        int j = high;
        while (i < j)
        {
            while (arr[i] <= pivot && i < high)
            {
                i++;
            }
            while (arr[j] > pivot)
            {
                j--;
            }
            if (i < j)
            {
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[low], arr[j]);
        return j;
    }
};

int main()
{
    srand(static_cast<int>(time(0)));
    
    int arr1[] = {-1, 3, -5, 7, -2, 0, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    Solution sol1;
    sol1.quickSort_deterministic(arr1, 0, n1 - 1);
    cout << "Sorted array (Deterministic QuickSort): ";
    for (int i = 0; i < n1; i++){
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    int arr2[] = {-1, 3, -5, 7, -2, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    Solution sol2;
    sol2.quickSort_randomized(arr2, 0, n2 - 1);
    cout << "Sorted array (Randomized QuickSort): ";
    for (int i = 0; i < n2; i++){
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}