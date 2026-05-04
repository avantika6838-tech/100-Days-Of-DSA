/* Problem: Delete First Occurrence of a Key - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer key

Output:
- Print the linked list elements after deletion, space-separated

Example:
Input:
5
10 20 30 40 50
30

Output:
10 20 40 50

Explanation:
Traverse list, find first node with key, remove it by adjusting previous node's next pointer.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

int main(){
    
    int n, key;
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

    scanf("%d", &key);

    struct Node *current = head, *prev = NULL;
    while(current != NULL){
        if(current->data == key){
            if(prev == NULL){ 
                head = current->next;
            }else{
                prev->next = current->next;
            }
            free(current);
            break;   
        }
        prev = current;
        current = current->next;
    }

    temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}
