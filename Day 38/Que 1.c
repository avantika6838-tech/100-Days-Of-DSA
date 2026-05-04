/*Problem: Deque (Double-Ended Queue)

A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

Common Operations:
1. push_front(value): Insert an element at the front of the deque.
2. push_back(value): Insert an element at the rear of the deque.
3. pop_front(): Remove an element from the front of the deque.
4. pop_back(): Remove an element from the rear of the deque.
5. front(): Return the front element of the deque.
6. back(): Return the rear element of the deque.
7. empty(): Check whether the deque is empty.
8. size(): Return the number of elements in the deque.

Additional Operations:
- clear(): Remove all elements from the deque.
- erase(): Remove one or more elements from the deque.
- swap(): Swap contents of two deques.
- emplace_front(): Insert an element at the front without copying.
- emplace_back(): Insert an element at the rear without copying.
- resize(): Change the size of the deque.
- assign(): Replace elements with new values.
- reverse(): Reverse the order of elements.
- sort(): Sort the elements in ascending order.

Time Complexity:
- push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
- clear, erase, resize, assign, reverse: O(n)
- sort: O(n log n)

Input:
- Sequence of deque operations with values (if applicable)

Output:
- Results of operations such as front, back, size, or the final state of the deque after all operations
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int size;
} Deque;

void init(Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
    dq->size = 0;
}

int empty(Deque* dq) {
    return dq->size == 0;
}

int full(Deque* dq) {
    return dq->size == MAX;
}

void push_front(Deque* dq, int val) {
    if (full(dq)) return;

    if (empty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->front = (dq->front - 1 + MAX) % MAX;
    }

    dq->arr[dq->front] = val;
    dq->size++;
}

void push_back(Deque* dq, int val) {
    if (full(dq)) return;

    if (empty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % MAX;
    }

    dq->arr[dq->rear] = val;
    dq->size++;
}

int pop_front(Deque* dq) {
    if (empty(dq)) return -1;

    int val = dq->arr[dq->front];

    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % MAX;
    }

    dq->size--;
    return val;
}

int pop_back(Deque* dq) {
    if (empty(dq)) return -1;

    int val = dq->arr[dq->rear];

    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + MAX) % MAX;
    }

    dq->size--;
    return val;
}

int front_val(Deque* dq) {
    if (empty(dq)) return -1;
    return dq->arr[dq->front];
}

int back_val(Deque* dq) {
    if (empty(dq)) return -1;
    return dq->arr[dq->rear];
}

int getSize(Deque* dq) {
    return dq->size;
}

void clear(Deque* dq) {
    dq->front = dq->rear = -1;
    dq->size = 0;
}

void reverse(Deque* dq) {
    if (empty(dq)) return;

    int i = dq->front;
    int j = dq->rear;

    for (int count = 0; count < dq->size / 2; count++) {
        int temp = dq->arr[i];
        dq->arr[i] = dq->arr[j];
        dq->arr[j] = temp;

        i = (i + 1) % MAX;
        j = (j - 1 + MAX) % MAX;
    }
}

void display(Deque* dq) {
    if (empty(dq)) {
        printf("Empty\n");
        return;
    }

    int i = dq->front;
    for (int count = 0; count < dq->size; count++) {
        printf("%d ", dq->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Deque dq;
    init(&dq);

    push_back(&dq, 10);
    push_back(&dq, 20);
    push_front(&dq, 5);

    display(&dq);

    printf("%d\n", pop_front(&dq)); 
    printf("%d\n", front_val(&dq)); 
    printf("%d\n", back_val(&dq));  

    reverse(&dq);
    display(&dq); 
    return 0;
}
