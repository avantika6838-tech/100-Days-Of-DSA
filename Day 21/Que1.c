/* Problem: Create and Traverse Singly Linked List

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the result

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50
*/

#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};

void display(struct node *head){
    struct node * temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main(){
    
    int i, value, n;
    struct node *head = NULL;
    struct node *ptr, *temp;

    printf("Enter the number of nodes = ");
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        printf("Enter the node %d value = ", i + 1);
        scanf("%d", &value);
        ptr = (struct node*)malloc(sizeof(struct node));
        ptr->data = value;
        ptr->next = NULL;
        if(head == NULL){
            head = ptr;
        }else{
            temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = ptr;
        }
    }

    printf("Linked List = ");
    display(head);

    return 0;
}
