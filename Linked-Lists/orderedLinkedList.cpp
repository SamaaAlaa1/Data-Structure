#include <iostream>
using namespace std;

struct Node {
    int data;       // Data part of the node
    Node* next;     // Pointer to the next node

    // Constructor to initialize a node
    Node(int value) : data(value), next(nullptr) {}
};

class OrderedLinkedList {
private:
    Node* head; // Pointer to the first node of the list
public:
    // Constructor to initialize an empty ordered linked list
    OrderedLinkedList() : head(nullptr) {}

    // Destructor to free memory
    ~OrderedLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Function to insert a node in sorted order
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr || head->data >= value) {
            newNode->next = head; // Insert at the beginning
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < value) {
                current = current->next; // Traverse to find the correct position
            }
            newNode->next = current->next; // Insert in the middle or end
            current->next = newNode;
        }
    }

    // Function to display the linked list
    void display() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Function to get the head of the list
    Node* getHead() {
        return head;
    }

    // Function to delete a node by value
    void deleteNode(int value) {
        if (head == nullptr) return; // If the list is empty, do nothing

        if (head->data == value) {
            Node* temp = head;
            head = head->next; // Move head to the next node
            delete temp;       // Delete the old head
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next; // Traverse the list to find the node
        }

        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next; // Unlink the node
            delete temp;                         // Delete the node
        }
    }
};