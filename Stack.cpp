/*
A stack is a linear simple data structure that can
only be accessed at one of its ends for data
storage and retrieval.

It is LIFO structure.

It resembles a stack of plates in a cafeteria.

A stack may have limited capacity or may be expandable.

Stacks are useful if data has to be stored and then retrieved in a reverse order.
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    // Constructor to initialize the stack
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }

    // Destructor to free memory
    ~Stack() {
        delete[] arr;
    }
    int top() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return arr[top];
    }
    void printStack() const {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    // Push an element onto the stack
    void push(int value) {
        if (isFull()) {
            throw overflow_error("Stack overflow");
        }
        arr[++top] = value;
    }

    // Pop an element from the stack
    int pop() {
        if (isEmpty()) {
            throw underflow_error("Stack underflow");
        }
        return arr[top--];
    }

    // Peek the top element of the stack
    int peek() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return arr[top];
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Check if the stack is full
    bool isFull() const {
        return top == capacity - 1;
    }

    // Get the current size of the stack
    int size() const {
        return top + 1;
    }
};

/////////////////////////////////////////////////////
/*
Stack usage example
*/
//Bracket delimiters checking
bool areBracketsBalanced(const string& expr) {
    // Create a stack to store opening brackets
    Stack stack(expr.length());

    // Iterate through each character in the expression
    for (char ch : expr) {
        // If the character is an opening bracket, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } 
        // If the character is a closing bracket
        else if (ch == ')' || ch == '}' || ch == ']') {
            // If the stack is empty, it means there is no matching opening bracket
            if (stack.isEmpty()) {
                return false;
            }
            // Pop the top element from the stack
            char top = stack.pop();
            // Check if the popped element matches the current closing bracket
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false; // Mismatched brackets
            }
        }
    }

    // If the stack is empty, all brackets are balanced; otherwise, they are not
    return stack.isEmpty();
}

/////////////////////////////////////////////////////
//Big Integer Addition
string addLargeNumbers(const string& num1, const string& num2) {
    Stack stack1(num1.length());
    Stack stack2(num2.length());
    Stack resultStack(max(num1.length(), num2.length()) + 1);

    // Push digits of num1 onto stack1
    for (char digit : num1) {
        stack1.push(digit - '0');
    }

    // Push digits of num2 onto stack2
    for (char digit : num2) {
        stack2.push(digit - '0');
    }

    int carry = 0;

    // Perform addition using the stacks
    while (!stack1.isEmpty() || !stack2.isEmpty() || carry != 0) {
        int digit1 = stack1.isEmpty() ? 0 : stack1.pop();
        int digit2 = stack2.isEmpty() ? 0 : stack2.pop();

        int sum = digit1 + digit2 + carry;
        resultStack.push(sum % 10);
        carry = sum / 10;
    }

    // Build the result string from the result stack
    string result;
    while (!resultStack.isEmpty()) {
        result += to_string(resultStack.pop());
    }

    return result;
}

/////////////////////////////////////////////////////
//Evaluation Postfix Expressions
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
            while (!operatorStack.isEmpty() && infixToPostfix(operatorStack.peek()) >= infixToPostfix(currentSymbol)) {
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

int main() {
   
    return 0;
}
