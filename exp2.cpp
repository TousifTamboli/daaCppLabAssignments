#include <iostream>
using namespace std;

// Function for binary search
int binarySearch(int arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2; // Calculate mid
        if (arr[mid] == target) {
            return mid; // Target found
        }
        if (arr[mid] > target) {
            return binarySearch(arr, left, mid - 1, target); // Search in left half
        }
        return binarySearch(arr, mid + 1, right, target); // Search in right half
    }
    return -1; // Target not found
}

int main() {
    int n, target;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements in sorted order:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Input elements
    }

    cout << "Enter the target element to search: ";
    cin >> target;

    int result = binarySearch(arr, 0, n - 1, target);
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }

    return 0;
}
