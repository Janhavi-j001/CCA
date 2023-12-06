#include <iostream>

// Function to merge two sorted subarrays into a single sorted array
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int *left_arr = new int[n1];
    int *right_arr = new int[n2];

    // Copy data to temporary arrays left_arr[] and right_arr[]
    for (i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        right_arr[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left_arr[], if there are any
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right_arr[], if there are any
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    // Delete the allocated memory for temporary arrays
    delete[] left_arr;
    delete[] right_arr;
}

// Function to perform Merge Sort on the array
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Recursively sort the first and second halves
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
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

    // Perform Merge Sort
    merge_sort(arr, 0, size - 1);

    std::cout << "Sorted Array: ";
    print_array(arr, size);

    return 0;
}
