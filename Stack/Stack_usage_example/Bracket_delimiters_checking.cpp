#include <iostream>
#include <stdexcept>
#include "../stack.h"
using namespace std;

/*
Stack usage example
*/
// Bracket delimiters checking
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
