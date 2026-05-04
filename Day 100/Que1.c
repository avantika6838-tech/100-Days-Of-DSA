#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int val, index;
};

void merge(struct Pair arr[], int left, int mid, int right, int count[]) {
    int i = left, j = mid + 1, k = 0;
    int rightCount = 0;

    struct Pair temp[right - left + 1];

    while (i <= mid && j <= right) {
        if (arr[i].val <= arr[j].val) {
            count[arr[i].index] += rightCount;
            temp[k++] = arr[i++];
        } else {
            rightCount++;
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        count[arr[i].index] += rightCount;
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
}

void mergeSort(struct Pair arr[], int left, int right, int count[]) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid, count);
    mergeSort(arr, mid + 1, right, count);

    merge(arr, left, mid, right, count);
}

void countSmaller(int nums[], int n) {
    struct Pair arr[n];
    int count[n];

    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].index = i;
        count[i] = 0;
    }

    mergeSort(arr, 0, n - 1, count);

    printf("Counts:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", count[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {5, 2, 6, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    countSmaller(nums, n);

    return 0;
}
