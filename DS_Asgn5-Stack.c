#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define SIZE 100

int top = -1;
char stack[MAX][SIZE];
char e[SIZE];

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(char str[])
{
    if (isFull())
    {
        printf("Stack overflow\n");
        return;
    }

    top++;
    strcpy(stack[top], str);
}

void pop(char e[])
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        e[0] = '\0';
        return;
    }

    strcpy(e, stack[top]);
    top--;
}

void resetStack()
{
    top = -1;
}

int check_operand_or_operator(char ch)
{
    if (isalnum((unsigned char)ch))
    {
        return 1;
    }

    if (ch == '+' || ch == '-' || ch == '^' ||
        ch == '*' || ch == '/')
    {
        return 0;
    }

    return 0;
}

int precedence(char ch)
{
    switch (ch)
    {
        case '^':
            return 3;

        case '*':
        case '/':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}


void Convert_Infix_to_Postfix(char arr[])
{
    char opStack[MAX];
    int topOp = -1;

    char result[SIZE] = "";
    int k = 0;

    for (int i = 0; arr[i] != '\0'; i++)
    {
        char ch = arr[i];

        if (isspace((unsigned char)ch))
        {
            continue;
        }

        if (isalnum((unsigned char)ch))
        {
            result[k++] = ch;
        }

        else if (ch == '(')
        {
            if (topOp < MAX - 1)
                opStack[++topOp] = ch;
        }

        else if (ch == ')')
        {
            while (topOp != -1 && opStack[topOp] != '(')
            {
                result[k++] = opStack[topOp--];
            }

            if (topOp != -1 && opStack[topOp] == '(')
            {
                topOp--;
            }
        }

        else
        {
            while (topOp != -1 &&
                   opStack[topOp] != '(' &&
                   (precedence(opStack[topOp]) > precedence(ch) ||
                    (precedence(opStack[topOp]) == precedence(ch) && ch != '^')))
            {
                result[k++] = opStack[topOp--];
            }

            if (topOp < MAX - 1)
                opStack[++topOp] = ch;
        }
    }

    while (topOp != -1)
    {
        if (opStack[topOp] != '(')
        {
            result[k++] = opStack[topOp];
        }

        topOp--;
    }

    result[k] = '\0';

    printf("Postfix expression: %s\n", result);
}


void Convert_Postfix_toPrefix(char arr1[])
{
    resetStack();

    int length = strlen(arr1);

    for (int i = 0; i < length; i++)
    {
        if (check_operand_or_operator(arr1[i]))
        {
            char temp[2] = {arr1[i], '\0'};
            push(temp);
        }
        else
        {
            char op[2] = {arr1[i], '\0'};
            char op1[SIZE], op2[SIZE];
            char result[SIZE];

            pop(op2);
            pop(op1);

            strcpy(result, op);
            strcat(result, op1);
            strcat(result, op2);

            push(result);
        }
    }

    pop(e);

    printf("Prefix expression: %s\n", e);
}


void Convert_Prefix_toInfix(char arr[])
{
    resetStack();

    int length = strlen(arr);

    for (int i = length - 1; i >= 0; i--)
    {
        if (check_operand_or_operator(arr[i]))
        {
            char temp[2] = {arr[i], '\0'};
            push(temp);
        }
        else
        {
            char op[2] = {arr[i], '\0'};
            char op1[SIZE], op2[SIZE];
            char result[SIZE];

            pop(op1);
            pop(op2);

            strcpy(result, "(");
            strcat(result, op1);
            strcat(result, op);
            strcat(result, op2);
            strcat(result, ")");

            push(result);
        }
    }

    pop(e);

    printf("Infix expression: %s\n", e);
}


int main()
{
    char arr1[] = "A*(B+C)/D";

    Convert_Infix_to_Postfix(arr1);


    char arr2[] = "AB+C*";

    Convert_Postfix_toPrefix(arr2);


    char arr3[] = "*A+BC";

    Convert_Prefix_toInfix(arr3);


    return 0;
}
