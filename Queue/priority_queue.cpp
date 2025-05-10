#include <iostream>
using namespace std;

// Priority Queue
/*
A priority queue is a queue whose elements
has priority and are dequeued according to their
priority and their queue position relative to other
elements with the same priority.
*/
class PriorityQueue
{
private:
    struct Node
    {
        int value;    // Value of the element
        int priority; // Priority of the element
    };

    Node *arr;    // Pointer to dynamically allocated array for storing elements
    int capacity; // Maximum capacity of the priority queue
    int size;     // Current number of elements in the priority queue

public:
    // Constructor to initialize the priority queue with a given capacity
    PriorityQueue(int capacity)
    {
        this->capacity = capacity; // Set the maximum capacity
        arr = new Node[capacity];  // Dynamically allocate memory for the priority queue
        size = 0;                  // Initialize the size to 0
    }

    // Destructor to release the dynamically allocated memory
    ~PriorityQueue()
    {
        delete[] arr; // Free the memory allocated for the priority queue
    }

    // Enqueue operation to add an element with a priority
    void enqueue(int value, int priority)
    {
        if (isFull())
        { // Check if the priority queue is full
            cout << "Priority Queue is full. Cannot enqueue " << value << endl;
            return; // Exit the function if the priority queue is full
        }

        // Insert the new element at the end
        arr[size].value = value;
        arr[size].priority = priority;
        size++;

        // Reorder the elements based on priority (higher priority first)
        for (int i = size - 1; i > 0; i--)
        {
            if (arr[i].priority > arr[i - 1].priority)
            {
                swap(arr[i], arr[i - 1]);
            }
            else
            {
                break;
            }
        }
    }

    // Dequeue operation to remove and return the element with the highest priority
    int dequeue()
    {
        if (isEmpty())
        { // Check if the priority queue is empty
            cout << "Priority Queue is empty. Cannot dequeue." << endl;
            return -1; // Return -1 to indicate an error
        }

        int value = arr[0].value; // Get the element with the highest priority
        // Shift all elements to the left
        for (int i = 0; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;       // Decrement the size of the priority queue
        return value; // Return the dequeued element
    }

    // Check if the priority queue is empty
    bool isEmpty() const
    {
        return size == 0; // Priority queue is empty if size is 0
    }

    // Check if the priority queue is full
    bool isFull() const
    {
        return size == capacity; // Priority queue is full if size equals capacity
    }

    // Get the current size of the priority queue
    int getSize() const
    {
        return size;
    }
};