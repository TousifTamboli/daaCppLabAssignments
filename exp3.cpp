#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to partition the array
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the last element as pivot
    int i = low - 1; // Index of smaller element
    for (int j = low; j < high; ++j) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            ++i; // Increment index of smaller element
            swap(arr[i], arr[j]); // Swap
        }
    }
    swap(arr[i + 1], arr[high]); // Place pivot element in correct position
    return (i + 1); // Return the pivot index
}

// Function to implement Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);
        // Recursively sort elements before and after the pivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];

    // Uncomment the below section to generate random numbers instead of user input
    /*
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }
    */

    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    cout << "Array before sorting: ";
    printArray(arr, n);

    // Perform Quick Sort
    clock_t start_time = clock();
    quickSort(arr, 0, n - 1);
    clock_t end_time = clock();

    cout << "Array after sorting: ";
    printArray(arr, n);

    // Calculate time taken for sorting
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken by Quick Sort: " << time_taken << " seconds" << endl;

    return 0;
}
