#include <iostream>

// Function to find the minimum and maximum elements in an array
void find_min_max(int arr[], int left, int right, int &min, int &max) {
    if (left == right) {
        // If there is only one element in the array
        min = arr[left];
        max = arr[right];
    } else if (right - left == 1) {
        // If there are two elements in the array
        min = (arr[left] < arr[right]) ? arr[left] : arr[right];
        max = (arr[left] > arr[right]) ? arr[left] : arr[right];
    } else {
        // If there are more than two elements, divide and conquer
        int mid = (left + right) / 2;
        int left_min, left_max, right_min, right_max;

        // Recursively find min and max in the left and right halves
        find_min_max(arr, left, mid, left_min, left_max);
        find_min_max(arr, mid + 1, right, right_min, right_max);

        // Combine the results
        min = (left_min < right_min) ? left_min : right_min;
        max = (left_max > right_max) ? left_max : right_max;
    }
}

// Driver program to test the function
int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int min, max;
    find_min_max(arr, 0, size - 1, min, max);

    std::cout << "Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << "\nMinimum Element: " << min << std::endl;
    std::cout << "Maximum Element: " << max << std::endl;

    return 0;
}
