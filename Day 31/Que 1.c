#include <stdio.h>
#include <stdlib.h>

#define MAX 1000  // maximum stack size

typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;

// Function to create a stack
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
        // Stack overflow (not required in problem, but safe check)
        return;
    }
    stack->arr[++stack->top] = val;
}

// Pop operation
void pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack->arr[stack->top--]);
}

// Display operation
void display(Stack* stack) {
    if (stack->top == -1) {
        printf("\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    Stack* stack = createStack(MAX);

    for (int i = 0; i < n; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int val;
            scanf("%d", &val);
            push(stack, val);
        } else if (op == 2) {
            pop(stack);
        } else if (op == 3) {
            display(stack);
        }
    }

    free(stack->arr);
    free(stack);
    return 0;
}
