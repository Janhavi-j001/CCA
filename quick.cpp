#include <iostream>

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (j >= i && arr[j] > pivot)
            j--;
        if (i <= j) {
            // Swap arr[i] and arr[j]
            std::swap(arr[i], arr[j]);
        } else {
            // Swap pivot (arr[low]) and arr[j]
            std::swap(arr[low], arr[j]);
            return j; // Return the pivot index
        }
    }
}

// Function to perform Quick Sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the subarrays
        quick_sort(arr, low, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, high);
    }
}

// Function to print an array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Driver program to test the functions
int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original Array: ";
    print_array(arr, size);

    // Perform Quick Sort
    quick_sort(arr, 0, size - 1);

    std::cout << "Sorted Array: ";
    print_array(arr, size);

    return 0;
}
