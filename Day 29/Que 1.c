#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main() {
    int n, k, i, x;

    scanf("%d", &n);
    if (n <= 0)
        return 0;

    struct node *head = NULL, *temp = NULL, *newnode = NULL;

    // Create linked list
    for (i = 0; i < n; i++) {
        scanf("%d", &x);

        newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = x;
        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
            temp = newnode;
        } else {
            temp->next = newnode;
            temp = newnode;
        }
    }

    // Read k
    scanf("%d", &k);

    // Find length and last node
    int len = 1;
    struct node *tail = head;

    while (tail->next != NULL) {
        tail = tail->next;
        len++;
    }

    // Adjust k
    k = k % len;

    if (k == 0) {
        // No rotation needed
        struct node *ptr = head;
        while (ptr != NULL) {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
        return 0;
    }

    // Make circular
    tail->next = head;

    // Move to new tail: (len - k) steps
    int steps = len - k;
    struct node *newTail = head;

    for (i = 1; i < steps; i++) {
        newTail = newTail->next;
    }

    // New head
    head = newTail->next;

    // Break circular link
    newTail->next = NULL;

    // Print rotated list
    struct node *ptr = head;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }

    return 0;
}
