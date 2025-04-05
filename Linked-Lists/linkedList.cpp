#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;       // Data part of the node
    Node* next;     // Pointer to the next node

    // Constructor to initialize a node
    Node(int value) : data(value), next(nullptr) {}
};

// LinkedList 
/**
 * Properties:
 * - The linked list is composed of nodes, where each node contains data and a pointer to the next node.
 * - The list maintains a pointer to the first node, referred to as the "head".
 * - If the list is empty, the head pointer is set to nullptr.
 * - Nodes are dynamically allocated and deallocated to manage memory efficiently.
 * - The linked list supports basic operations such as appending nodes, displaying the list, and deleting nodes by value.
 *
 * Key Features:
 * - Dynamic Size: The linked list can grow or shrink dynamically as nodes are added or removed.
 * - Sequential Access: Nodes are accessed sequentially starting from the head.
 * - Memory Management: The destructor ensures that all dynamically allocated nodes are properly deallocated to prevent memory leaks.
 */
class LinkedList {
private:
    Node* head; // Pointer to the first node of the list

public:
    // Constructor to initialize an empty linked list
    LinkedList() : head(nullptr) {}

    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Function to add a node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode; // If the list is empty, set head to the new node
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next; // Traverse to the end of the list
            }
            temp->next = newNode; // Link the last node to the new node
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

// Main function to demonstrate the LinkedList class
int main() {
    LinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);

    cout << "Linked List: ";
    list.display();

    list.deleteNode(20);
    cout << "After deleting 20: ";
    list.display();

    return 0;
}