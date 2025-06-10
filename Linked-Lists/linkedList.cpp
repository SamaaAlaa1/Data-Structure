#include <iostream>
using namespace std;
/*
Ways to build linked lists:
Forward
New node always inserted at end of the linked list

Backward
New node always inserted at the beginning of the list
/////////////////////////////
Two types of linked lists: sorted, unsorted

*/
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
    void insertAtEnd(int value) {
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
    
    // Function to add a node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head; // Point the new node to the current head
        head = newNode;       // Update head to the new node
    }

    // Function to insert a node at a specific position
    void insertAt(int value, int position) {
        if (position <= 0) {
            insertAtBeginning(value); // Insert at the beginning if position is 0 or negative
            return;
        }

        Node* newNode = new Node(value);
        Node* current = head;

        // Traverse to the node just before the desired position
        for (int i = 0; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }

        if (current == nullptr) {
            insertAtEnd(value); // If position is beyond the end, insert at the end
        } else {
            newNode->next = current->next; // Link the new node to the next node
            current->next = newNode;       // Link the previous node to the new node
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


int main() {
    LinkedList list;

    list.insertAtEnd(92);  
    list.insertAtEnd(63);  
    list.insertAtEnd(75);  

    cout << "Linked List: ";
    list.display();

    Node* current = list.getHead();      // current = node with data 92
    Node* head = current->next;          // head = node with data 63 (like head = current->link)


    cout << "current->data: " << current->data << endl; // 92
    cout << "current->next->data: " << current->next->data << endl; // 63
    cout << "head->data: " << head->data << endl; // 63
    cout << "head->next->data: " << head->next->data << endl; // 75

    if (head->next->next == nullptr) {
        cout << "head->next->next: nullptr (end of list)" << endl;
    }

    Node* last = head->next->next;
    if (last != nullptr && last->next != nullptr) {
        cout << "head->next->next->data: " << last->next->data << endl;
    } else {
        cout << "head->next->next->next: nullptr (does not exist)" << endl;
    }

    return 0;
}