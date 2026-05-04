#include <stdio.h>
#include <stdlib.h>

// Node for linked list (used in buckets)
struct Node {
    float data;
    struct Node* next;
};

// Insert node in sorted order (for each bucket)
struct Node* insertSorted(struct Node* head, float value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // Insert at beginning or empty list
    if (head == NULL || value < head->data) {
        newNode->next = head;
        return newNode;
    }

    // Traverse and insert
    struct Node* curr = head;
    while (curr->next != NULL && curr->next->data <= value) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;

    return head;
}

// Bucket sort function
void bucketSort(float arr[], int n) {
    int i;

    // Step 1: Create n buckets
    struct Node** buckets = (struct Node**)malloc(n * sizeof(struct Node*));
    for (i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // Step 2: Distribute elements into buckets
    for (i = 0; i < n; i++) {
        int index = n * arr[i];   // bucket index
        buckets[index] = insertSorted(buckets[index], arr[i]);
    }

    // Step 3: Concatenate buckets
    int k = 0;
    for (i = 0; i < n; i++) {
        struct Node* curr = buckets[i];
        while (curr != NULL) {
            arr[k++] = curr->data;
            curr = curr->next;
        }
    }

    // Free memory
    for (i = 0; i < n; i++) {
        struct Node* curr = buckets[i];
        while (curr != NULL) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(buckets);
}

// Function to print array
void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    float arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
