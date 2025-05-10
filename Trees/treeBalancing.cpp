/*
   Tree Balancing Techniques
   =========================
   The disadvantage of a binary search tree is that
   its height can be as large as n-1.

   A balanced binary search tree maintains O(log n) operations by ensuring
   the tree height remains logarithmic relative to the number of nodes.

   Thus, our goal is to keep the height of a binary
   search tree O(log n)
   The AVL tree and Red-Black tree are two types of balanced binary search trees.
   ==========================
  -A balanced tree is one who has the difference
  in height of both subtrees of any node in the tree
  is either one or zero.

  -A perfectly balanced tree is one who is balanced and has all the leaves at the same level.
   ==========================
   Technique 1: Continuously restructure the tree
   when new elements arrive that cause imbalance
   in the tree. So, we always keep the tree
   balanced. (AVL, DSW)

   Technique 2:
   Reorder the data and then build the tree so that it is balanced.
   ===========================
   AVL Trees
   Locally change the tree to rebalance it after an insertion or deletion.
   Named after Adel’son-Vel’skii and Landis.
   The height of every left and right subtrees of a node differ by one at most.
   No guarantee that the resulting tree is perfectly balanced.
   AVL tree is a binary search tree in which for every node in the tree, the height of the left and
   right subtrees differ by at most 1.
 */

#include <iostream>
#include <algorithm>
using namespace std;

class AVLTree
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        int height;

        Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    // Utility functions
    int height(Node *node)
    {
        return node ? node->height : 0;
    }

    int balanceFactor(Node *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node *node)
    {
        if (node)
        {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    // Rotation functions
    Node *rightRotate(Node *y)
    {
        /*
         * Right Rotation (LL Case):
         *        y                  x
         *       / \                / \
         *      x   C     →        A   y
         *     / \                    / \
         *    A   B                  B   C
         */
        Node *x = y->left;
        Node *B = x->right;

        x->right = y;
        y->left = B;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *leftRotate(Node *x)
    {
        /*
         * Left Rotation (RR Case):
         *      x                  y
         *     / \                / \
         *    A   y     →        x   C
         *       / \            / \
         *      B   C          A   B
         */
        Node *y = x->right;
        Node *B = y->left;

        y->left = x;
        x->right = B;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *balance(Node *node)
    {
        if (!node)
            return nullptr;

        updateHeight(node);
        int bf = balanceFactor(node);

        // Left heavy
        if (bf > 1)
        {
            if (balanceFactor(node->left) >= 0)
            { // LL case
                return rightRotate(node);
            }
            else
            { // LR case
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // Right heavy
        if (bf < -1)
        {
            if (balanceFactor(node->right) <= 0)
            { // RR case
                return leftRotate(node);
            }
            else
            { // RL case
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert with balancing
    Node *insert(Node *node, int value)
    {
        if (!node)
            return new Node(value);

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }
        else
        {
            return node; // No duplicates
        }

        return balance(node);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    // Delete with balancing
    Node *deleteNode(Node *node, int value)
    {
        if (!node)
            return nullptr;

        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }
        else
        {
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                Node *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node)
            return nullptr;

        return balance(node);
    }

    Node *findMin(Node *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

    // Traversal methods (same as BST)
    void inOrder(Node *node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void display()
    {
        inOrder(root);
        cout << endl;
    }
};

/*
Tree Tool – You must try it

https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

http://www.qmatica.com/DataStructures/Trees/AVL/AVLTree.html

http://groups.engin.umd.umich.edu/CIS/course.des/cis350/treetool/index.html

http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_avl.aspx

http://www.cmcrossroads.com/bradapp/ftp/src/libs/C++/AvlTrees.html
*/
int main()
{
    cout << "AVL Tree Example:\n";
    AVLTree avl;
    for (int i : {10, 20, 30, 40, 50, 25})
    {
        avl.insert(i);
    }
    avl.display();
    return 0;
}