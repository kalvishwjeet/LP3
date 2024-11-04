#include <iostream>
#include <cstdlib>  // For random number generation
#include <ctime>    // For seeding random number generator
using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Deterministic partition function (choosing the last element as the pivot)
int partitionDeterministic(int arr[], int low, int high) {
    int pivot = arr[high];  // Choose the last element as the pivot
    int i = low - 1;        // Index of the smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized partition function (choosing a random pivot)
int partitionRandomized(int arr[], int low, int high) {
    // Choose a random pivot index between low and high
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]);  // Swap the random pivot with the last element
    return partitionDeterministic(arr, low, high);  // Use the deterministic partition logic
}

// Quick Sort function (Deterministic version)
void quickSortDeterministic(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionDeterministic(arr, low, high);  // Find partition index

        // Recursively sort elements before and after the partition
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, pi + 1, high);
    }
}

// Quick Sort function (Randomized version)
void quickSortRandomized(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionRandomized(arr, low, high);  // Find partition index

        // Recursively sort elements before and after the partition
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

// Utility function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));  // Seed the random number generator

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int* arr1 = new int[n];  // Array for deterministic quick sort
    int* arr2 = new int[n];  // Array for randomized quick sort

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
        arr2[i] = arr1[i];  // Copy elements to arr2 for randomized quick sort
    }

    cout << "\nOriginal array: ";
    printArray(arr1, n);

    // Deterministic Quick Sort
    quickSortDeterministic(arr1, 0, n - 1);
    cout << "Array after Deterministic Quick Sort: ";
    printArray(arr1, n);

    // Randomized Quick Sort
    quickSortRandomized(arr2, 0, n - 1);
    cout << "Array after Randomized Quick Sort: ";
    printArray(arr2, n);

    // Clean up dynamic arrays
    delete[] arr1;
    delete[] arr2;

    return 0;
}
