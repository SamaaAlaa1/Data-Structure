#include <iostream>
using namespace std;
//Circular Linked Lists -> Last node points to the first node
// Node structure for the circular linked list
struct Node
{
    int data;   // Data part of the node
    Node *next; // Pointer to the next node
};

// Circular Linked List class
class CircularLinkedList
{
private:
    Node *head; // Pointer to the head of the list

public:
    // Constructor to initialize the list
    CircularLinkedList() : head(nullptr) {}

    // Destructor to free memory
    ~CircularLinkedList()
    {
        if (head)
        {
            Node *temp = head;
            do
            {
                Node *nextNode = temp->next;
                delete temp;
                temp = nextNode;
            } while (temp != head);
        }
    }

    // Function to check if the list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Function to insert a node at the end of the list
    void insertAtEnd(int value)
    {
        Node *newNode = new Node{value, nullptr};
        if (isEmpty())
        {
            head = newNode;
            head->next = head; // Point to itself to make it circular
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head; // Complete the circular link
        }
    }

    // Function to insert a node at the beginning of the list
    void insertAtBeginning(int value)
    {
        Node *newNode = new Node{value, nullptr};
        if (isEmpty())
        {
            head = newNode;
            head->next = head; // Point to itself to make it circular
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode; // Update head to the new node
        }
    }

    // Function to delete a node with a specific value
    void deleteNode(int value)
    {
        if (isEmpty())
        {
            cout << "List is empty. Nothing to delete.\n";
            return;
        }

        Node *current = head;
        Node *previous = nullptr;

        // Find the node to delete
        do
        {
            if (current->data == value)
            {
                if (current == head)
                {
                    // If the node to delete is the head
                    Node *temp = head;
                    if (head->next == head)
                    {
                        // If there's only one node
                        head = nullptr;
                    }
                    else
                    {
                        Node *last = head;
                        while (last->next != head)
                        {
                            last = last->next;
                        }
                        head = head->next;
                        last->next = head;
                    }
                    delete temp;
                }
                else
                {
                    // If the node to delete is not the head
                    previous->next = current->next;
                    delete current;
                }
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);

        cout << "Value not found in the list.\n";
    }

    // Function to display the list
    void display() const
    {
        if (isEmpty())
        {
            cout << "List is empty.\n";
            return;
        }

        Node *temp = head;
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

// Main function to demonstrate the CircularLinkedList class
int main()
{
    CircularLinkedList cll;

    cll.insertAtEnd(10);
    cll.insertAtEnd(20);
    cll.insertAtEnd(30);
    cll.display(); // Output: 10 20 30

    cll.insertAtBeginning(5);
    cll.display(); // Output: 5 10 20 30

    cll.deleteNode(20);
    cll.display(); // Output: 5 10 30

    cll.deleteNode(50); // Output: Value not found in the list.

    return 0;
}