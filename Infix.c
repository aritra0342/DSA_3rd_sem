#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int operandStack[MAX];
char operatorStack[MAX];
int operandTop = -1, operatorTop = -1;

// Push an operand onto the operand stack
void pushOperand(int value) {
    operandStack[++operandTop] = value;
}

// Push an operator onto the operator stack
void pushOperator(char op) {
    operatorStack[++operatorTop] = op;
}

// Pop an operand from the operand stack
int popOperand() {
    return operandStack[operandTop--];
}

// Pop an operator from the operator stack
char popOperator() {
    return operatorStack[operatorTop--];
}

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply an operation to two operands
int applyOperation(int a, int b, char op) {
    if (op == '+') return a + b;
    else if (op == '-') return a - b;
    else if (op == '*') return a * b;
    else if (op == '/') return a / b;
    return 0;
}

// Evaluate infix expression
int evaluate(char* expression) {
    int i = 0;
    while (expression[i] != '\0') {
        // Skip spaces
        if (expression[i] == ' ') {
            i++;
        }
        // If it's a number, parse it and push onto the operand stack
        else if (isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            pushOperand(num);
            i--; // Adjust for next character
        }
        // If it's an open parenthesis, push it onto the operator stack
        else if (expression[i] == '(') {
            pushOperator(expression[i]);
        }
        // If it's a closing parenthesis, solve until '(' is found
        else if (expression[i] == ')') {
            while (operatorStack[operatorTop] != '(') {
                int b = popOperand();
                int a = popOperand();
                char op = popOperator();
                pushOperand(applyOperation(a, b, op));
            }
            popOperator(); // Pop the '(' from the stack
        }
        
        else {
            while (operatorTop != -1 && precedence(operatorStack[operatorTop]) >= precedence(expression[i])) {
                int b = popOperand();
                int a = popOperand();
                char op = popOperator();
                pushOperand(applyOperation(a, b, op));
            }
            pushOperator(expression[i]);
        }
        i++;
    }
    
    
    while (operatorTop != -1) {
        int b = popOperand();
        int a = popOperand();
        char op = popOperator();
        pushOperand(applyOperation(a, b, op));
    }
    
    return popOperand();
}

int main() {
    char expression[] = "3 + 5 * ( 2 - 8 )";
    printf("Result: %d\n", evaluate(expression));
    return 0;
}
