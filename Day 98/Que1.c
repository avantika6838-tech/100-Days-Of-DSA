#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start, end;
};

int compare(const void *a, const void *b) {
    return ((struct Interval *)a)->start - ((struct Interval *)b)->start;
}


void mergeIntervals(struct Interval arr[], int n) {
    if (n <= 0) return;

  
    qsort(arr, n, sizeof(struct Interval), compare);

    
    struct Interval result[n];
    int index = 0;

    
    result[index] = arr[0];

    
    for (int i = 1; i < n; i++) {
        if (arr[i].start <= result[index].end) {
            // Overlapping → merge
            if (arr[i].end > result[index].end)
                result[index].end = arr[i].end;
        } else {
            // No overlap → move to next
            index++;
            result[index] = arr[i];
        }
    }

    // Print merged intervals
    printf("Merged Intervals:\n");
    for (int i = 0; i <= index; i++) {
        printf("[%d, %d] ", result[i].start, result[i].end);
    }
    printf("\n");
}

// Driver code
int main() {
    struct Interval arr[] = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeIntervals(arr, n);

    return 0;
}
