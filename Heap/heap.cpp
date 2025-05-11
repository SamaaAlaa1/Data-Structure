#include <iostream>
#include "heap.h"
using namespace std;

/*
A heap is a nearly complete binary tree with the following two properties:

-Structural property: all levels are full, except possibly the last one, which is filled from left to right
-Max (heap) property: for any node x Parent(x) ≥ x
================
A heap can be stored as an array A:
- The root element will be at Arr[0]
- For any given node at position i, its left child will be at position 2i + 1 and its right child at position 2i + 2
- The parent of a node at position i will be at position (i - 1) / 2
- The last element of the heap will be at position (n - 1) / 2
- The height of a heap is log(n)
- The maximum number of nodes at height h is 2^h
- The maximum number of nodes in a heap of height h is 2^(h + 1) - 1
=================
Max heap property:
- The value of each node is greater than or equal to the values of its children
- The maximum value is at the root node

Min heap property:
- The value of each node is less than or equal to the values of its children
- The minimum value is at the root node
=================
*/

// Moves the element at the given index up the heap to maintain the heap property
template <typename T, int MAX_SIZE>
void Heap<T, MAX_SIZE>::heapifyUp(int index) {
    while (index > 0 && compare(data[index], data[parent(index)])) {
        swap(data[index], data[parent(index)]);
        index = parent(index);
    }
}

// Moves the element at the given index down the heap to maintain the heap property
template <typename T, int MAX_SIZE>
void Heap<T, MAX_SIZE>::heapifyDown(int index) {
    int smallestOrLargest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < currentSize && compare(data[left], data[smallestOrLargest])) {
        smallestOrLargest = left;
    }

    if (right < currentSize && compare(data[right], data[smallestOrLargest])) {
        smallestOrLargest = right;
    }

    if (smallestOrLargest != index) {
        swap(data[index], data[smallestOrLargest]);
        heapifyDown(smallestOrLargest);
    }
}

// Compares two elements based on the heap type (min-heap or max-heap)
template <typename T, int MAX_SIZE>
bool Heap<T, MAX_SIZE>::compare(const T& a, const T& b) const {
    return isMinHeap ? a < b : a > b;
}

// Adds a new element to the heap
template <typename T, int MAX_SIZE>
void Heap<T, MAX_SIZE>::push(const T& value) {
    if (currentSize == MAX_SIZE) {
        throw overflow_error("Heap is full");
    }
    data[currentSize] = value;
    heapifyUp(currentSize);
    currentSize++;
}

// Removes the top element (min or max) from the heap
template <typename T, int MAX_SIZE>
void Heap<T, MAX_SIZE>::pop() {
    if (empty()) {
        throw underflow_error("Heap is empty");
    }
    data[0] = data[currentSize - 1];
    currentSize--;
    heapifyDown(0);
}

// Returns the top element (min or max) of the heap
template <typename T, int MAX_SIZE>
T Heap<T, MAX_SIZE>::top() const {
    if (empty()) {
        throw underflow_error("Heap is empty");
    }
    return data[0];
}
