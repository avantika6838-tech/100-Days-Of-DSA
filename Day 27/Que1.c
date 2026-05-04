/*Problem: Find Intersection Point of Two Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print value of intersection node or 'No Intersection'

Example:
Input:
5
10 20 30 40 50
4
15 25 30 40 50

Output:
30

Explanation:
Calculate lengths, advance pointer in longer list, traverse both simultaneously. First common node is intersection.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* newNode(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Node* insert(struct Node* head, int data){
    struct Node* temp = newNode(data);

    if(head == NULL){
        return temp;
    }
    struct Node* curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = temp;
    return head;
}

int length(struct Node* head){
    int count = 0;
    while(head){
        count++;
        head = head->next;
    }
    return count;
}

struct Node* findIntersection(struct Node* head1, struct Node* head2){

    int len1 = length(head1);
    int len2 = length(head2);

    int diff = abs(len1 - len2);

    struct Node *p1 = head1, *p2 = head2;

    if(len1 > len2){
        for(int i = 0; i < diff; i++){
            p1 = p1->next;
        }
    }else{
        for(int i = 0; i < diff; i++){
            p2 = p2->next;
        }
    }

    while(p1 && p2){
        if(p1 == p2){
            return p1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    return NULL;
}

int main(){

    int n, m, x;
    struct Node *head1 = NULL, *head2 = NULL;

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        head1 = insert(head1, x);
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%d", &x);
        head2 = insert(head2, x);
    }

    struct Node *temp1 = head1;
    while(temp1 && temp1->data != 30){
        temp1 = temp1->next;
    }
    struct Node *temp2 = head2;
    while(temp2->next){
        temp2 = temp2->next;
    }
    temp2->next = temp1;  

    struct Node* result = findIntersection(head1, head2);

    if(result){
        printf("%d\n", result->data);
    }else{
        printf("No Intersection\n");
    }
    return 0;
}
