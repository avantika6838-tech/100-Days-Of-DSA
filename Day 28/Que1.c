#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main() {
    int n, i, x;

    scanf("%d", &n);

    if (n <= 0)
        return 0;

    struct node *head = NULL, *temp = NULL, *newnode = NULL;

    // Create nodes
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

    // Make circular
    temp->next = head;

    // Traverse circular list
    struct node *ptr = head;

    if (head != NULL) {
        do {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        } while (ptr != head);
    }

    return 0;
}
