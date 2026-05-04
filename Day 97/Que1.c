#include <stdio.h>
#include <stdlib.h>
struct Meeting {
    int start, end;
};

// Comparator for sorting by start time
int compare(const void *a, const void *b) {
    return ((struct Meeting *)a)->start - ((struct Meeting *)b)->start;
}

// Min Heap functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int heap[], int index) {
    while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
        swap(&heap[(index - 1) / 2], &heap[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(int heap[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}


void push(int heap[], int *size, int value) {
    heap[*size] = value;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

void pop(int heap[], int *size) {
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
}


int top(int heap[]) {
    return heap[0];
}

int minMeetingRooms(struct Meeting arr[], int n) {
    // Step 1: Sort by start time
    qsort(arr, n, sizeof(struct Meeting), compare);

    int *heap = (int *)malloc(n * sizeof(int));
    int size = 0;

  
    push(heap, &size, arr[0].end);


    for (int i = 1; i < n; i++) {
        if (arr[i].start >= top(heap)) {
            pop(heap, &size);  
        }
        push(heap, &size, arr[i].end);
    }

    free(heap);
    return size; 
}

int main() {
    struct Meeting arr[] = {
        {0, 30}, {5, 10}, {15, 20}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Minimum meeting rooms required = %d\n", minMeetingRooms(arr, n));

    return 0;
}
