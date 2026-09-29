#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int values[MAX], vtop = -1;
char ops[MAX];
int otop = -1;

void pushValue(int x) {
    values[++vtop] = x;
}

int popValue() {
    return values[vtop--];
}

void pushOp(char x) {
    ops[++otop] = x;
}

char popOp() {
    return ops[otop--];
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++)
                result *= a;
            return result;
        }
    }
    return 0;
}

int evaluate(char exp[]) {
    for (int i = 0; exp[i] != '\0'; i++) {

        if (exp[i] == ' ')
            continue;

        if (isdigit(exp[i])) {
            pushValue(exp[i] - '0');
        }
        else if (exp[i] == '(') {
            pushOp(exp[i]);
        }
        else if (exp[i] == ')') {
            while (otop != -1 && ops[otop] != '(') {
                char op = popOp();
                int b = popValue();
                int a = popValue();
                pushValue(applyOperation(a, b, op));
            }
            popOp(); // remove '('
        }
        else {
            while (otop != -1 &&
                   ops[otop] != '(' &&
                   precedence(ops[otop]) >= precedence(exp[i])) {

                char op = popOp();
                int b = popValue();
                int a = popValue();

                pushValue(applyOperation(a, b, op));
            }

            pushOp(exp[i]);
        }
    }

    while (otop != -1) {
        char op = popOp();
        int b = popValue();
        int a = popValue();

        pushValue(applyOperation(a, b, op));
    }

    return popValue();
}

int main() {
    char expression[MAX];

    printf("Enter infix expression: ");
    scanf("%[^\n]", expression);

    printf("Result = %d\n", evaluate(expression));

    return 0;
}
