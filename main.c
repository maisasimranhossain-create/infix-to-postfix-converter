
#include <stdio.h>

#define MAX 100

char stack[MAX];
int top = -1;

// PUSH: Insert an element into stack
void push(char value)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        stack[++top] = value;
    }
}

// POP: Remove the top element
char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

// PEEK: View the top element
char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

// Check operator precedence
int precedence(char op)
{
    if (op == '^')
        return 3;

    else if (op == '*' || op == '/')
        return 2;

    else if (op == '+' || op == '-')
        return 1;

    else
        return 0;
}

// Convert Infix to Postfix
void infixToPostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    char ch;

    top = -1;

    while (infix[i] != '\0')
    {
        ch = infix[i];

        // If operand, add directly to output
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'))
        {
            postfix[j++] = ch;
        }

        // If opening bracket
        else if (ch == '(')
        {
            push(ch);
        }

        // If closing bracket
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            if (top != -1)
                pop();
        }

        // If operator
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' || ch == '^')
        {
            while (top != -1 && peek() != '(' &&
                  (precedence(peek()) > precedence(ch) ||
                  (precedence(peek()) == precedence(ch) && ch != '^')))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }

        i++;
    }

    // Pop remaining operators
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

// Main function
int main()
{
    char infix[MAX], postfix[MAX];

    printf("INIFX TO POSTFIX CONVERTER\n");

    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
