#include <stdio.h>
#include <stdlib.h>

#define MAX 1000  // maximum stack size

typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;

// Create stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

// Push operation
void push(Stack* stack, int val) {
    if (stack->top == stack->capacity - 1) {
        // Overflow check (not required in problem, but safe)
        return;
    }
    stack->arr[++stack->top] = val;
}

// Pop operation
void pop(Stack* stack) {
    if (stack->top == -1) {
        // Underflow check
        return;
    }
    stack->top--;
}

// Display stack from top to bottom
void display(Stack* stack) {
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    Stack* stack = createStack(MAX);

    // Push n integers
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        push(stack, val);
    }

    int m;
    scanf("%d", &m);

    // Perform m pops
    for (int i = 0; i < m; i++) {
        pop(stack);
    }

    // Display remaining stack
    display(stack);

    free(stack->arr);
    free(stack);
    return 0;
}
