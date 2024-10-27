#include <stdio.h>
#define MAX 100  // Define the maximum size of the stack

int stack[MAX];   // Array to store stack elements
int top = -1;    // Initialize the top of the stack

// Function to push an element onto the stack
void push(int value) 
{
    if (top == MAX - 1) {  
        printf("Stack Overflow\n");
    } else {
        top++;               
        stack[top] = value; 
        printf("%d pushed onto stack\n", value);
    }
}

// Function to display the stack contents

void display()
{
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements are: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main() {
    push(10);  
    push(20);
    push(30);

    display(); 

    return 0;
}
