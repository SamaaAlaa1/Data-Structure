#include <iostream>
#include <stdexcept>

template <typename T>
class ArrayBasedList {
private:
    T* array;          // Pointer to the array
    int capacity;      // Maximum capacity of the list
    int size;          // Current number of elements in the list

    // function to resize the array when needed
    void resize(int newCapacity) {
        T* newArray = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    // Constructor
    ArrayBasedList(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Initial capacity must be greater than 0");
        }
        array = new T[capacity];
    }

    // Destructor
    ~ArrayBasedList() {
        delete[] array;
    }

    // Add an element to the end of the list
    void add(const T& element) {
        if (size == capacity) {
            resize(capacity * 2); // Double the capacity if the array is full
        }
        array[size++] = element;
    }

    // Insert an element at a specific index
    void insert(int index, const T& element) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize(capacity * 2);
        }
        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = element;
        size++;
    }

    // Remove an element at a specific index
    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        if (size <= capacity / 4 && capacity > 10) {
            resize(capacity / 2); // Shrink the capacity if the array is too empty
        }
    }

    // Get an element at a specific index
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    // Set an element at a specific index
    void set(int index, const T& element) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        array[index] = element;
    }

    // Get the current size of the list
    int getSize() const {
        return size;
    }
    // Find the index of the first occurrence of an element
    // Time Complexity: O(n)
    int indexOf(const T& element) const {
        for (int i = 0; i < size; i++) {
            if (array[i] == element) {
                return i;
            }
        }
        return -1; // Return -1 if the element is not found
    }

    // Check if the list contains a specific element
    // Time Complexity: O(n)
    bool contains(const T& element) const {
        return indexOf(element) != -1;
    }

    // Clear all elements in the list
    // Time Complexity: O(1)
    void clear() {
        size = 0;
        resize(10); // Reset to initial capacity
    }
    // Check if the list is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Print all elements in the list
    void print() const {
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Example usage
int main() {
    ArrayBasedList<int> list;

    list.add(10);
    list.add(20);
    list.add(30);
    list.print(); // Output: 10 20 30

    list.insert(1, 15);
    list.print(); // Output: 10 15 20 30

    list.remove(2);
    list.print(); // Output: 10 15 30

    std::cout << "Element at index 1: " << list.get(1) << std::endl; // Output: 15

    list.set(1, 25);
    list.print(); // Output: 10 25 30

    return 0;
}