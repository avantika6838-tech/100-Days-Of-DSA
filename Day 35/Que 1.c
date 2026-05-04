/*Implement Queue using Stacks

Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10000

typedef struct{
    int s1[MAX];
    int s2[MAX];
    int top1;
    int top2;
} MyQueue;

MyQueue* myQueueCreate(){
    MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
    q->top1 = -1;
    q->top2 = -1;
    return q;
}

void myQueuePush(MyQueue* obj, int x){
    obj->s1[++obj->top1] = x;
}

int myQueuePop(MyQueue* obj){
    if(obj->top2 == -1){
        while(obj->top1 != -1){
            obj->s2[++obj->top2] = obj->s1[obj->top1--];
        }
    }
    return obj->s2[obj->top2--];
}

int myQueuePeek(MyQueue* obj){
    if(obj->top2 == -1){
        while(obj->top1 != -1){
            obj->s2[++obj->top2] = obj->s1[obj->top1--];
        }
    }
    return obj->s2[obj->top2];
}

bool myQueueEmpty(MyQueue* obj){
    return (obj->top1 == -1 && obj->top2 == -1);
}

void myQueueFree(MyQueue* obj){
    free(obj);
}
