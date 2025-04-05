#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class ArrayBasedList {
private:
    T* array;
    int capacity;
    int size;

    void resize(int newCapacity) {
        T* newArray = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i]; // O(n)
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    // Constructor – O(1)
    ArrayBasedList(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        if (initialCapacity <= 0) throw invalid_argument("Initial capacity must be greater than 0");
        array = new T[capacity];
    }

    // Destructor – O(1)
    ~ArrayBasedList() {
        delete[] array;
    }

    // Copy constructor – O(n)
    ArrayBasedList(const ArrayBasedList& other) {
        capacity = other.capacity;
        size = other.size;
        array = new T[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i]; // O(n)
        }
    }

    // Assignment operator overloading – O(n)
    ArrayBasedList& operator=(const ArrayBasedList& other) {
        if (this != &other) {
            delete[] array;
            capacity = other.capacity;
            size = other.size;
            array = new T[capacity];
            for (int i = 0; i < size; i++) {
                array[i] = other.array[i]; // O(n)
            }
        }
        return *this;
    }

    // isEmpty – O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // isFull – O(1)
    bool isFull() const {
        return size == capacity;
    }

    // listSize – O(1)
    int listSize() const {
        return size;
    }

    // maxListSize – O(1)
    int maxListSize() const {
        return capacity;
    }

    // print – O(n)
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    // isItemAtEqual – O(1)
    bool isItemAtEqual(int index, const T& item) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        return array[index] == item;
    }

    // insertAt – O(n)
    void insertAt(int index, const T& element) {
        if (index < 0 || index > size) throw out_of_range("Index out of range");
        if (isFull()) resize(capacity * 2);
        for (int i = size; i > index; i--) {
            array[i] = array[i - 1]; // shift right – O(n)
        }
        array[index] = element;
        size++;
    }

    // insertEnd – O(1)
    void insertEnd(const T& element) {
        if (isFull()) resize(capacity * 2);
        array[size++] = element;
    }

    // removeAt – O(n)
    void removeAt(int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1]; // shift left – O(n)
        }
        size--;
    }

    // retrieveAt – O(1)
    T retrieveAt(int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        return array[index];
    }

    // replaceAt – O(1)
    void replaceAt(int index, const T& element) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        array[index] = element;
    }

    // clearList – O(1)
    void clearList() {
        size = 0;
        resize(10); // optional: reset capacity – O(1)
    }

    // seqSearch – O(n)
    int seqSearch(const T& item) const {
        for (int i = 0; i < size; i++) {
            if (array[i] == item) return i;
        }
        return -1;
    }

    // insert – O(n)
    void insert(const T& item) {
        insertEnd(item); // default behavior
    }

    // remove – O(n)
    void remove(const T& item) {
        int index = seqSearch(item); // O(n)
        if (index != -1) removeAt(index); // O(n)
    }
};
