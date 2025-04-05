#include <iostream>
using namespace std;

// Node structure for the doubly linked list
/*
Linked list in which every node has a next pointer and a back pointer
Every node contains address of next node
Except last node

Every node contains address of previous node
Except the first node
*/
struct Node
{
    int data;   // Data stored in the node
    Node *prev; // Pointer to the previous node
    Node *next; // Pointer to the next node

    // Constructor to initialize a new node
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// DoublyLinkedList class
class DoublyLinkedList
{
private:
    Node *head; // Pointer to the head of the list
    Node *tail; // Pointer to the tail of the list

public:
    // Constructor to initialize an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to free memory
    ~DoublyLinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Function to add a node at the end of the list
    void append(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        { // If the list is empty
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode; // Link the current tail to the new node
            newNode->prev = tail; // Link the new node back to the current tail
            tail = newNode;       // Update the tail to the new node
        }
    }

    // Function to add a node at the beginning of the list
    void prepend(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        { // If the list is empty
            head = tail = newNode;
        }
        else
        {
            newNode->next = head; // Link the new node to the current head
            head->prev = newNode; // Link the current head back to the new node
            head = newNode;       // Update the head to the new node
        }
    }

    // Function to delete a node with a specific value
    void deleteValue(int value)
    {
        Node *current = head;
        while (current)
        {
            if (current->data == value)
            {
                if (current->prev)
                { // If it's not the first node
                    current->prev->next = current->next;
                }
                else
                { // If it's the first node
                    head = current->next;
                }
                if (current->next)
                { // If it's not the last node
                    current->next->prev = current->prev;
                }
                else
                { // If it's the last node
                    tail = current->prev;
                }
                delete current; // Free the memory of the node
                return;
            }
            current = current->next;
        }
    }

    // Function to display the list from head to tail
    void displayForward() const
    {
        Node *current = head;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Function to display the list from tail to head
    void displayBackward() const
    {
        Node *current = tail;
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // Function to check if the list is empty
    bool isEmptyList() const
    {
        return head == nullptr;
    }

    // Function to get the first element of the list
    int front() const
    {
        if (head)
        {
            return head->data;
        }
        throw runtime_error("List is empty");
    }

    // Function to get the last element of the list
    int back() const
    {
        if (tail)
        {
            return tail->data;
        }
        throw runtime_error("List is empty");
    }
};

int main()
{
    DoublyLinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);

    cout << "List after appending 10, 20, 30: ";
    list.displayForward();

    list.prepend(5);
    cout << "List after prepending 5: ";
    list.displayForward();

    list.deleteValue(20);
    cout << "List after deleting 20: ";
    list.displayForward();

    cout << "List displayed backward: ";
    list.displayBackward();

    return 0;
}