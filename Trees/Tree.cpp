/*
A tree data structure consists of nodes and arcs.
Every node has one parent but may have one or more children.
Top node is root. Root has no parent.
Nodes with no children are called leaves.

Each node is reachable from the root with a unique sequence of arcs called path.
The number of arcs in a path is the length of thepath.
The level of a node is the length of the path from the root to the node + 1.
The height of a non-empty tree is the maximum level of a node in the tree.
The height of an empty tree is zero.
The height of a single node tree is 1.
A single node tree is the only case when the root is also a leaf.
The level of any node is between 1 and the tree height.

A binary tree is a tree whose nodes have at most two children per node.

A complete binary tree is a binary tree that satisfies the following conditions:
-Every non-terminal nodes has 2 children
-Leaves are all at the same level
///////////////////////////////////////////////////////////////////////
Binary Search Trees
A binary search tree is a binary tree that satisfies the following conditions:

-Every node n in its left sub-tree has a value
less than the value stored in n.

-Every node n in its right sub-tree has a value
greater than the value stored in n.
/////////////////////////////////////////////////////////////////////
Complexity of Searching in a BST:

Measured by the number of comparisons done,
which depends on the nodes encountered on
the path from the root to the node searched for.

So, complexity is the length of the path leading to this node +1;

= log n

Worst case = n
*/

#include <iostream>
using namespace std;

// Definition of a Node in the Binary Search Tree
class Node
{
public:
    int data;    // Value stored in the node
    Node *left;  // Pointer to the left child
    Node *right; // Pointer to the right child

    // Constructor to initialize a node with a value
    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node *root; // Pointer to the root of the tree

    // Helper function to insert a value into the tree
    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            // If the current node is null, create a new node
            return new Node(value);
        }
        if (value < node->data)
        {
            // If the value is less than the current node's data, go to the left subtree
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            // If the value is greater than the current node's data, go to the right subtree
            node->right = insert(node->right, value);
        }
        return node; // Return the unchanged node pointer
    }

    // Helper function to perform an in-order traversal
    void inOrderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderTraversal(node->left);  // Visit left subtree
        cout << node->data << " ";     // Visit current node
        inOrderTraversal(node->right); // Visit right subtree
    }

    // Helper function to search for a value in the tree
    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false; // Value not found
        }
        if (node->data == value)
        {
            return true; // Value found
        }
        if (value < node->data)
        {
            return search(node->left, value); // Search in the left subtree
        }
        else
        {
            return search(node->right, value); // Search in the right subtree
        }
    }
    /*
    Time Complexity:
    - Best Case: O(1), when the value is found at the root.
    - Average Case: O(log n), for a balanced binary search tree, as the search space is halved at each step.
    - Worst Case: O(n), for a skewed binary search tree (all nodes are in a single line, like a linked list).
    */

    // find the minimum value node in a subtree
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    //delete a value from the tree
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node; // Value not found
        }

        if (value < node->data) {
            // If the value is less than the current node's data, go to the left subtree
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            // If the value is greater than the current node's data, go to the right subtree
            node->right = deleteNode(node->right, value);
        } else {
            // Node to be deleted found
            if (node->left == nullptr) {
                // Node with only right child or no child
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                // Node with only left child
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

public:
    // Function to delete a value from the BST
    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

public:
    // Constructor to initialize an empty BST
    BST()
    {
        root = nullptr;
    }

    // Function to insert a value into the BST
    void insert(int value)
    {
        root = insert(root, value);
    }

    // Function to perform an in-order traversal of the BST
    void inOrderTraversal()
    {
        inOrderTraversal(root);
        cout << endl;
    }

    // Function to search for a value in the BST
    bool search(int value)
    {
        return search(root, value);
    }

    /*
    Depth-First Traversal is visiting all the node by going as deep as possible and then
    backtracking by moving one level up and then going as deep as possible,

    Depth-First Traversal uses recursion to yield elegant simple algorithms.
    But it puts a big burden on the stack if the tree is huge.
    */
    void preOrderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->data << " ";      // Visit current node
        preOrderTraversal(node->left);  // Visit left subtree
        preOrderTraversal(node->right); // Visit right subtree
    }

    void postOrderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        postOrderTraversal(node->left);  // Visit left subtree
        postOrderTraversal(node->right); // Visit right subtree
        cout << node->data << " ";       // Visit current node
    }

    // Public function to perform pre-order traversal
    void preOrderTraversal()
    {
        preOrderTraversal(root);
        cout << endl;
    }

    // Public function to perform post-order traversal
    void postOrderTraversal()
    {
        postOrderTraversal(root);
        cout << endl;
    }
};

// Example usage
int main()
{
    BST tree;

    // Insert values into the BST
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Perform in-order traversal
    cout << "In-order Traversal: ";
    tree.inOrderTraversal();

    // Search for values in the BST
    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (tree.search(90) ? "Found" : "Not Found") << endl;

    return 0;
}
