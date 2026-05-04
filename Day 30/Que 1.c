/* Problem: Polynomial Using Linked List - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of terms)
- Next n lines: two integers (coefficient and exponent)

Output:
- Print polynomial in standard form, e.g., 10x^4 + 20x^3 + 30x^2 + 40x + 50

Example:
Input:
5
10 4
20 3
30 2
40 1
50 0

Output:
10x^4 + 20x^3 + 30x^2 + 40x + 50

Explanation:
Each node stores coefficient and exponent. Traverse nodes to print polynomial in decreasing exponent order.
*/

#include<stdio.h>
#include<stdlib.h>

struct node{
    int coeff;
    int exp;
    struct node *next;
};

int main(){
    
    struct node *head = NULL, *temp = NULL, *ptr = NULL;
    int n, i;

    printf("Enter number of terms = ");
    scanf("%d", &n);


    for(i = 0; i < n; i++){
        ptr = (struct node*)malloc(sizeof(struct node));

        printf("Enter coefficient and exponent = ");
        scanf("%d %d", &ptr->coeff, &ptr->exp);

        ptr->next = NULL;

        if(head == NULL){
            head = ptr;
            temp = ptr;
        }else{
            temp->next = ptr;
            temp = ptr;
        }
    }

    temp = head;
    while(temp != NULL){
        if(temp->exp == 0){
            printf("%d", temp->coeff);
        }else if(temp->exp == 1){
            printf("%dx", temp->coeff);
        }else{
            printf("%dx^%d", temp->coeff, temp->exp);
        }if(temp->next != NULL){
            printf(" + ");
        }
        temp = temp->next;
    }

    return 0;
}
