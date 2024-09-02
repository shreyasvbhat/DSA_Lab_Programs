/*
Develop a menu driven program to convert infix expression to postfix expression using stack and evaluate 
the postfix expression. 
(Test for nested parenthesized expressions) Note: Define Stack structure and implement the operations. 
Use different stacks for conversion and evaluation. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define MIN_VAL -2147483648

typedef struct {
    void *stk;
    int top, capacity;
} Stack;

Stack *createStack(int isDoubleStack) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    if (stack == NULL) {
        printf("\nMemory Allocation Failed...\n");
        exit(1);
    } else {
        stack->capacity = 20, stack->top = -1;
        stack->stk = malloc(stack->capacity * (isDoubleStack ? sizeof(double) : sizeof(char)));

        if (stack->stk == NULL) {
            printf("\nMemory Allocation Failed...\n");
            exit(1);
        }
    }

    return stack;
}

void pushChar(Stack *stack, char data) {
    if (stack->top == stack->capacity - 1) {
        stack->stk = realloc(stack->stk, (stack->capacity *= 2) * sizeof(char));
    }

    *((char *)stack->stk + ++stack->top) = data;
}

void pushFloat(Stack *stack, double data) {
    if (stack->top == stack->capacity - 1) {
        stack->stk = realloc(stack->stk, (stack->capacity *= 2) * sizeof(double));
    }

    *((double *)stack->stk + ++stack->top) = data;
}

char popChar(Stack *stack) {
    return stack->top == -1 ? '\0' : *((char *)stack->stk + stack->top--);
}

double popFloat(Stack *stack) {
    return stack->top == -1 ? '\0' : *((double *)stack->stk + stack->top--);
}

char peekChar(Stack *stack) {
    return stack->top == -1 ? '\0' : *((char *)stack->stk + stack->top);
}

char associativity(char operator) {
    return (operator == '^' || operator == '$') ? 'R' : 'L';
}

int precedence(char operator) {
    if (operator == '^' || operator == '$') {
        return 3;
    } else if (operator == '/' || operator == '*') {
        return 2;
    } else if (operator == '+' || operator == '-') {
        return 1;
    }
    
    return -1;
}

void infixToPostfix(char *infix, char *postfix) {
    int pos = -1;
    Stack *stack = createStack(0);

    for (int i = 0; i < strlen(infix); i++) {
        char currChar = infix[i];

        if (currChar == '(') {
            pushChar(stack, '(');
        } else if (currChar == ')') {
            while (peekChar(stack) != '(') {
                postfix[++pos] = popChar(stack);
            }

            popChar(stack);
        } else if (isalnum(currChar)) {
            postfix[++pos] = currChar;
        } else {
            while (peekChar(stack) && (precedence(peekChar(stack)) > precedence(currChar) || precedence(peekChar(stack)) == precedence(currChar) && associativity(currChar) == 'L')) {
                postfix[++pos] = popChar(stack);
            }

            pushChar(stack, currChar);
        }
    }

    while (peekChar(stack)) {
        postfix[++pos] = popChar(stack);
    }
    postfix[++pos] = '\0';
}

double eval(double op1, double op2, char operator) {
    switch (operator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        case '^':
        case '$':
            return pow(op1, op2);
    }

    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == '$';
}

double evaluatePostfix(char postfix[]) {
    Stack *stack = createStack(1);

    for (int i = 0; i < strlen(postfix); i++) {
        char currChar = postfix[i];

        if (isdigit(currChar)) {
            pushFloat(stack, currChar - '0');
        } else if (isOperator(currChar)) {
            double op2 = popFloat(stack), op1 = popFloat(stack);
            pushFloat(stack, eval(op1, op2, currChar));
        } else {
            printf("\nEncountered an Invalid Character...\n");
            return MIN_VAL;
        }
    }

    if (stack->top) {
        printf("\nInvalid Expression...\n");
        return MIN_VAL;
    } else {
        return popFloat(stack);
    }
}

void main() {
    char infix[100], postfix[100], postfixExp[100];
    int choice;

    do {
        printf("\n******** MENU ********\n");
        printf("1. Infix Expression to Postfix Expression.\n");
        printf("2. Evaluate Valid Postfix Expression.\n");
        printf("3. Exit.\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter a Valid Infix Expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);

                printf("\nGiven Infix Expression: %s\n", infix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 2:
                printf("\nEnter the Valid Postfix Expression: ");
                scanf("%s", postfixExp);

                double res = evaluatePostfix(postfixExp);
                if (res != MIN_VAL) {
                    printf("\nResult: %.3f\n", res);
                }
                break;

            case 3:
                printf("\nThank You...\n");
                break;
            
            default:
                printf("\nInvalid Choice...\n");
                break;
        }
    } while (choice != 3);
}