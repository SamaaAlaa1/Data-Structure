// stack.h
#ifndef STACK_H
#define STACK_H

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int size);
    ~Stack();
    int topValue() const;
    void printStack() const;
    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
};

#endif
