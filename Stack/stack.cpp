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
#include "stack.h" // Assuming you have a stack.h file
using namespace std;

// Constructor to initialize the stack
Stack::Stack(int size) {
    arr = new int[size];
    capacity = size;
    top = -1;
}

// Destructor to free memory
Stack::~Stack() {
    delete[] arr;
}

// Return the top value of the stack
int Stack::topValue() const {
    if (isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    return arr[top];
}

// Print all elements in the stack
void Stack::printStack() const {
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
void Stack::push(int value) {
    if (isFull()) {
        throw overflow_error("Stack overflow");
    }
    arr[++top] = value;
}

// Pop an element from the stack
int Stack::pop() {
    if (isEmpty()) {
        throw underflow_error("Stack underflow");
    }
    return arr[top--];
}

// Peek the top element of the stack
int Stack::peek() const {
    if (isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    return arr[top];
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return top == -1;
}

// Check if the stack is full
bool Stack::isFull() const {
    return top == capacity - 1;
}

// Get the current size of the stack
int Stack::size() const {
    return top + 1;
}
