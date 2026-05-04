/*Problem: Implement Selection Sort - Implement the algorithm.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the sorted array or search result

Example:
Input:
5
64 34 25 12 22

Output:
12 22 25 34 64*/

#include <stdio.h>

int main() {
    int n, i, j, min, temp;

    // Input size of array
    scanf("%d", &n);

    int arr[n];

    // Input array elements
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Selection Sort
    for(i = 0; i < n-1; i++) {
        min = i; // Assume current element is minimum

        // Find smallest element in unsorted part
        for(j = i+1; j < n; j++) {
            if(arr[j] < arr[min]) {
                min = j;
            }
        }

        // Swap elements
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    // Print sorted array
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
