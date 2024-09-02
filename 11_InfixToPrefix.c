/*
Develop a menu driven program to convert infix expression to Prefix expression using stack and evaluate 
the Prefix expression. 
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

void pushDouble(Stack *stack, double data) {
    if (stack->top == stack->capacity - 1) {
        stack->stk = realloc(stack->stk, (stack->capacity *= 2) * sizeof(double));
    }

    *((double *)stack->stk + ++stack->top) = data;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

char popChar(Stack *stack) {
    return isEmpty(stack) ? '\0' : *((char *)stack->stk + stack->top--);
}

double popDouble(Stack *stack) {
    return isEmpty(stack) ? 0.0 : *((double *)stack->stk + stack->top--);
}

char peekChar(Stack *stack) {
    return isEmpty(stack) ? '\0' : *((char *)stack->stk + stack->top);
}

void reverse(char *str) {
    int start = 0, end = strlen(str) - 1;

    while (start < end) {
        char temp = str[start];
        str[start++] = str[end];
        str[end--] = temp;
    }
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

void infixToPrefix(char *infix, char *prefix) {
    int pos = -1;
    Stack *stack = createStack(0);

    for (int i = strlen(infix) - 1; i >= 0; i--) {
        char currChar = infix[i];

        if (currChar == ')') {
            pushChar(stack, ')');
        } else if (currChar == '(') {
            while (peekChar(stack) != ')') {
                prefix[++pos] = popChar(stack);
            }

            popChar(stack);
        } else if (isalnum(currChar)) {
            prefix[++pos] = currChar;
        } else {
            while (!isEmpty(stack) && (precedence(peekChar(stack)) > precedence(currChar) || precedence(peekChar(stack)) == precedence(currChar) && associativity(currChar) == 'R')) {
                prefix[++pos] = popChar(stack);
            }

            pushChar(stack, currChar);
        }
    }

    while (!isEmpty(stack)) {
        prefix[++pos] = popChar(stack);
    }
    prefix[++pos] = '\0';

    reverse(prefix);
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

    return 0.0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == '$';
}

double evaluatePrefix(char prefix[]) {
    Stack *stack = createStack(1);

    for (int i = strlen(prefix) - 1; i >= 0; i--) {
        char currChar = prefix[i];

        if (isdigit(currChar)) {
            pushDouble(stack, currChar - '0');
        } else if (isOperator(currChar)) {
            double op1 = popDouble(stack), op2 = popDouble(stack);
            pushDouble(stack, eval(op1, op2, currChar));
        } else {
            printf("\nEncountered an Invalid Character...\n");
            return MIN_VAL;
        }
    }

    if (stack->top) {
        printf("\nInvalid Expression...\n");
        return MIN_VAL;
    } else {
        return popDouble(stack);
    }
}

void main() {
    char infix[100], prefix[100], prefixExp[100];
    int choice;

    do {
        printf("\n******** MENU ********\n");
        printf("1. Infix Expression to Prefix Expression.\n");
        printf("2. Evaluate Valid Prefix Expression.\n");
        printf("3. Exit.\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter a Valid Infix Expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);

                printf("\nGiven Infix Expression: %s\n", infix);
                printf("Prefix Expression: %s\n", prefix);
                break;

            case 2:
                printf("\nEnter the Valid Prefix Expression (Containing only digits from 0 through 9): ");
                scanf("%s", prefixExp);

                double res = evaluatePrefix(prefixExp);
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