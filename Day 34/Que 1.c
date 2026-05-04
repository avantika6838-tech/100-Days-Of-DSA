#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Node definition for stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Push operation
void push(Node** top, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = *top;
    *top = newNode;
}

// Pop operation
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        exit(1);
    }
    Node* temp = *top;
    int val = temp->data;
    *top = temp->next;
    free(temp);
    return val;
}

// Evaluate postfix expression
int evaluatePostfix(char* expr) {
    Node* stack = NULL;

    char* token = strtok(expr, " ");
    while (token != NULL) {
        // If operand, push to stack
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atoi(token));
        }
        // If operator, pop two operands and apply
        else {
            int b = pop(&stack);
            int a = pop(&stack);
            int result;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: printf("Invalid operator\n"); exit(1);
            }
            push(&stack, result);
        }
        token = strtok(NULL, " ");
    }

    return pop(&stack);
}

int main() {
    char expr[200];
    // Read entire line (postfix expression)
    fgets(expr, sizeof(expr), stdin);
    // Remove newline if present
    expr[strcspn(expr, "\n")] = '\0';

    int result = evaluatePostfix(expr);
    printf("%d\n", result);

    return 0;
}
