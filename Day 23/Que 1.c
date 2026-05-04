/* Problem: Merge Two Sorted Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print the merged linked list elements, space-separated

Example:
Input:
5
10 20 30 40 50
4
15 25 35 45

Output:
10 15 20 25 30 35 40 45 50

Explanation:
Compare nodes of both lists, append smaller to result, continue until all nodes are merged.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* createNode(int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int value){
    struct Node* newNode = createNode(value);

    if(head == NULL){
        return newNode;
    }

    struct Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
    return head;
}

void printList(struct Node* head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
}

int main(){
    int i, n, m, value;
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &value);
        list1 = insertEnd(list1, value);
    }

    scanf("%d", &m);
    for(i = 0; i < m; i++){
        scanf("%d", &value);
        list2 = insertEnd(list2, value);
    }

    struct Node *merged = NULL, *tail = NULL;

    if(list1 == NULL){
        merged = list2;
    }else if(list2 == NULL){
        merged = list1;
    }else{
        if(list1->data <= list2->data){
            merged = list1;
            list1 = list1->next;
        }else{
            merged = list2;
            list2 = list2->next;
        }

        tail = merged;

        while(list1 != NULL && list2 != NULL){
            if(list1->data <= list2->data){
                tail->next = list1;
                list1 = list1->next;
            }else{
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        if(list1 != NULL){
            tail->next = list1;
        }else{
            tail->next = list2;
        }
    }

    printList(merged);

    return 0;
}
