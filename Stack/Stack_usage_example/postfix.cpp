#include <iostream>
#include "../stack.h"
using namespace std;

// Evaluation Postfix Expressions
/*
Algorithm: maintain a stack and scan the
postfix expression from left to right
– If the element is a number, push it into the
stack
– If the element is a operator O, pop twice
and get A and B respectively. Calculate
BOA and push it back to the stack
– When the expression is ended, the number
in the stack is the final answer
*/
int evaluatePostfix(const string& expression) {
    Stack stack(expression.length());

    for (char ch : expression) {
        // If the character is a digit, push it onto the stack
        if (isdigit(ch)) {
            stack.push(ch - '0');
        }
        // If the character is an operator, pop two elements and perform the operation
        else {
            int operand2 = stack.pop();
            int operand1 = stack.pop();

            if (ch == '+') {
                stack.push(operand1 + operand2);
            } else if (ch == '-') {
                stack.push(operand1 - operand2);
            } else if (ch == '*') {
                stack.push(operand1 * operand2);
            } else if (ch == '/') {
                if (operand2 == 0) {
                    throw runtime_error("Division by zero");
                }
                stack.push(operand1 / operand2);
            } else {
                throw invalid_argument("Invalid operator");
            }
        }
    }

    // The final result will be the only element left in the stack
    return stack.pop();
}

// Transform Infix to Postfix
int infixToPostfix(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Transform infix expression to postfix expression
/*
Algorithm: maintain a stack and scan the
postfix expression from left to right
– When we get a number, output it
– When we get an operator O, pop the top
element in the stack until there is no
operator having higher priority then O and
then push(O) into the stack
– When the expression is ended, pop all the
operators remain in the stack
*/
string convertInfixToPostfix(const string& infixExpression) {
    Stack operatorStack(infixExpression.length());
    string postfixExpression;

    for (char currentSymbol : infixExpression) {
        // If the symbol is an operand, add it to the postfix expression
        if (isalnum(currentSymbol)) {
            postfixExpression += currentSymbol;
        }
        // If the symbol is '(', push it onto the stack
        else if (currentSymbol == '(') {
            operatorStack.push(currentSymbol);
        }
        // If the symbol is ')', pop and append until '(' is encountered
        else if (currentSymbol == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfixExpression += operatorStack.pop();
            }
            if (!operatorStack.isEmpty() && operatorStack.peek() == '(') {
                operatorStack.pop(); // Remove '(' from the stack
            }
        }
        // If the symbol is an operator
        else if (isOperator(currentSymbol)) {
            while (!operatorStack.isEmpty() &&
                   infixToPostfix(operatorStack.peek()) >= infixToPostfix(currentSymbol)) {
                postfixExpression += operatorStack.pop();
            }
            operatorStack.push(currentSymbol);
        }
    }

    // Pop all remaining operators from the stack
    while (!operatorStack.isEmpty()) {
        postfixExpression += operatorStack.pop();
    }

    return postfixExpression;
}
