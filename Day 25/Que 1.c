/*Problem: Count Occurrences of an Element in Linked List - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of nodes)
- Second line: n space-separated integers (linked list elements)
- Third line: integer key (element to be counted)

Output:
- Print the number of times the key appears in the linked list

Example:
Input:
6
10 20 30 20 40 20
20

Output:
3
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

int main(){
    int n, key, count = 0;
    scanf("%d", &n);

    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    for(int i = 0; i < n; i++){
        int value;
        scanf("%d", &value);

        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = NULL;

        if(head == NULL){
            head = newNode;
            temp = newNode;
        }else{
            temp->next = newNode;
            temp = newNode;
        }
    }

    printf("Enter the key = ");
    scanf("%d", &key);

    temp = head;
    while(temp != NULL){
        if(temp->data == key){
            count++;
        }
        temp = temp->next;
    }

    printf("%d", count);

    return 0;
}
