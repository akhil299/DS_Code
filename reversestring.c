#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

int top = -1;
char stack[MAX];

void push(char item);
char pop();

int main() {
    char str[MAX];
    unsigned int i;

    printf("Enter the string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove the newline character

    // Push characters onto the stack
    for (i = 0; i < strlen(str); i++) {
        push(str[i]);
    }

    // Pop characters from the stack to reverse the string
    for (i = 0; i < strlen(str); i++) {
        str[i] = pop();
    }

    printf("\nReversed string is: ");
    puts(str);

    return 0;
}

void push(char item) {
    if (top == (MAX - 1)) {
        printf("\nStack Overflow\n");
        return;
    }
    stack[++top] = item;
}

char pop() {
    if (top == -1) {
        printf("\nStack Underflow\n");
        exit(1);
    }
    return stack[top--];
}
