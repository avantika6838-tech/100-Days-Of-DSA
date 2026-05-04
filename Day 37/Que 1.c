/* Problem Statement:
Implement a Priority Queue using an array. An element with smaller value has higher priority.

Supported Operations:
- insert x
- delete
- peek

Input Format:
- First line contains integer N
- Next N lines contain operations

Output Format:
- Print the deleted or peeked element
- Print -1 if the queue is empty

Example:
Input:
5
insert 30
insert 10
insert 20
delete
peek

Output:
10
20
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int heap[MAX];
int size = 0;


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else break;
    }
}

void heapifyDown(int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            swap(&heap[index], &heap[smallest]);
            index = smallest;
        } else break;
    }
}


void insert(int x) {
    heap[size] = x;
    size++;
    heapifyUp(size - 1);
}

int delete() {
    if (size == 0) return -1;

    int val = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);

    return val;
}


int peek() {
    if (size == 0) return -1;
    return heap[0];
}


int main() {
    int N;
    scanf("%d", &N);

    char op[10];
    int x;

    for (int i = 0; i < N; i++) {
        scanf("%s", op);

        if (op[0] == 'i') {   
            scanf("%d", &x);
            insert(x);
        } 
        else if (op[0] == 'd') {  
            printf("%d\n", delete());
        } 
        else if (op[0] == 'p') { 
            printf("%d\n", peek());
        }
    }

    return 0;
}
