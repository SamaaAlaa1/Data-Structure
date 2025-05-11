#ifndef HEAP_H
#define HEAP_H

#include <iostream>

template <typename T, int MAX_SIZE>
class Heap {
private:
    T data[MAX_SIZE];
    int currentSize = 0;
    bool isMinHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    bool compare(const T& a, const T& b) const;

public:
    explicit Heap(bool minHeap = true) : isMinHeap(minHeap) {}

    void push(const T& value);
    void pop();
    T top() const;
    bool empty() const { return currentSize == 0; }
    int size() const { return currentSize; }
};


#endif // HEAP_H
