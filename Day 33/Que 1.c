#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Stack implementation
typedef struct {
    char arr[MAX];
    int top;
} Stack;

void push(Stack* s, char c) {
    s->arr[++s->top] = c;
}

char pop(Stack* s) {
    return s->arr[s->top--];
}

char peek(Stack* s) {
    return s->arr[s->top];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char* infix) {
    Stack s;
    s.top = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // If operand, print directly
        if (isalnum(c)) {
            printf("%c", c);
        }
        // If '(', push to stack
        else if (c == '(') {
            push(&s, c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                printf("%c", pop(&s));
            }
            pop(&s); // remove '('
        }
        // Operator
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                printf("%c", pop(&s));
            }
            push(&s, c);
        }
    }

    // Pop remaining operators
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");
}

int main() {
    char infix[MAX];
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
