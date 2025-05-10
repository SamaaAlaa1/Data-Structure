#include <iostream>
#include "../stack.h"
using namespace std;

// Big Integer Addition
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
