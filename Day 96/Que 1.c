#include <stdio.h>
#include <stdlib.h>

// Merge function that also counts inversions
int merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;     // left subarray
    int j = mid + 1;  // right subarray
    int k = left;     // temp array index
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1); // count inversions
        }
    }

    // Copy remaining elements
    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    // Copy back to original array
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

// Recursive merge sort function
int mergeSort(int arr[], int temp[], int left, int right) {
    int mid, inv_count = 0;

    if (left < right) {
        mid = (left + right) / 2;

        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);

        inv_count += merge(arr, temp, left, mid, right);
    }

    return inv_count;
}

// Function to count inversions
int countInversions(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    int result = mergeSort(arr, temp, 0, n - 1);
    free(temp);
    return result;
}

// Driver code
int main() {
    int arr[] = {2, 4, 1, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int inv = countInversions(arr, n);
    printf("Number of inversions = %d\n", inv);

    return 0;
}
