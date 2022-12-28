#include "SplayTree.h"
#include "dsexceptions.h"
#include <iostream>
#include <string>

using namespace std;

template <typename Comparable>
SplayTree<Comparable>::SplayTree()
{
    nullNode = new BinaryNode;
    nullNode->left = nullNode->right = nullNode;
    nullNode->value = 0;
    root = nullNode;
}

template <typename Comparable>
SplayTree<Comparable>::SplayTree(const SplayTree &rhs)
{
    nullNode = new BinaryNode;
    nullNode->left = nullNode->right = nullNode;
    nullNode->value = 0;
    root = clone(rhs.root);
}

template <typename Comparable>
SplayTree<Comparable>::SplayTree(SplayTree &&rhs) : root{rhs.root}, nullNode{rhs.nullNode}
{
    rhs.root = nullptr;
    rhs.nullNode = nullptr;
}

template <typename Comparable>
SplayTree<Comparable>::~SplayTree()
{
    makeEmpty();
    delete nullNode;
}

template <typename Comparable>
bool SplayTree<Comparable>::isEmpty() const
{
    return root == nullNode;
}

template <typename Comparable>
void SplayTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root, true);
}

template <typename Comparable>
void SplayTree<Comparable>::makeEmpty()
{
    while (!isEmpty())
    {
        findMax(); // Splay max item to root
        remove(root->element);
    }
}

template <typename Comparable>
void SplayTree<Comparable>::printTree(BinaryNode *t,  bool flg) const
{
    static int lineCount;

    if (flg)
        lineCount = 0;
    
    if (t != t->left)
    {
        cout << "(" << t->element << "," << t->value << ")  ";
        lineCount++;
        if(lineCount % 5 == 0)
            cout << endl;
        printTree(t->left, false);
        printTree(t->right, false);
    }
}

// If the tree is empty, return false
// otherwise, splay the node with element x or the node that
// is last accessed in the search process to the root
// Check whether the root element is equal x
// In the case of a successful search, splaying
// should occur from the found node up to the root. If search fails, splaying should start at the last
// node visited before the failure is detected.
template <typename Comparable>
bool SplayTree<Comparable>::search(const Comparable &x)
{
    if (isEmpty())
        return false;
    splay(x, root);

    return root->element == x;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Assignment 05: Q3
///////////////////////////////////////////////////////////////////////////////////////////////
// Copy and paste you developed methods in q1 & q2 for the following five methods
///////////////////////////////////////////////////////////////////////////////////////////////
//   Find the smallest item in the tree.
//   Not the most efficient implementation (uses two passes), but has correct amortized behavior.
//   A good alternative is to first call find with parameter smaller than any item in the tree, then call findMin.
//   Return the smallest item or throw UnderflowException if empty.
//   Note: you need to splay the min node to the root
template <typename Comparable>
const Comparable &SplayTree<Comparable>::findMin()
{
    if (isEmpty())
        throw UnderflowException{};

    BinaryNode *ptr = root;

    while (ptr->left != nullNode)
        ptr = ptr->left;
    
    splay (ptr->element, root);
    return ptr->element;
}

// Find the largest item in the tree.
// Not the most efficient implementation (uses two passes), but has correct amortized behavior.
// A good alternative is to first call find with parameter larger than any item in the tree, then call findMax.
// Return the largest item or throw UnderflowException if empty.
// Note: you need to splay the max node to the root
template <typename Comparable>
const Comparable &SplayTree<Comparable>::findMax()
{
    if (isEmpty())
        throw UnderflowException{};
    
    BinaryNode *ptr = root;

    while (ptr->right != nullNode)
        ptr = ptr->right;
    
    splay (ptr->element, root);
    return ptr->element;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
template <typename Comparable>
void SplayTree<Comparable>::rightRotate(BinaryNode *&k2)
{
    BinaryNode *k1 = k2->left;
    k2->left = k1 ->right;
    k1->right = k2;
    k2 = k1;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
template <typename Comparable>
void SplayTree<Comparable>::leftRotate(BinaryNode *&k1)
{
    BinaryNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

//  Internal method to perform a top-down splay.
//  The last accessed node becomes the new root.
//  The splay tree code depends on the accessed item going to the root.
//  t is the root of the subtree to splay.
template <typename Comparable>
void SplayTree<Comparable>::splay(const Comparable &x, BinaryNode *&t)
{
    BinaryNode *leftTreeMax, *rightTreeMin;
    static BinaryNode header;

    header.left = header.right = nullNode;
    leftTreeMax = rightTreeMin = &header;

    nullNode->element = x; // Guarantee a match

    for (;;)
        if (x < t->element)
        {
            if (x < t->left->element)
                rightRotate(t);
            if (t->left == nullNode)
                break;
            // Link Right
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        }
        else if (t->element < x)
        {
            if (t->right->element < x)
                leftRotate(t);
            if (t->right == nullNode)
                break;
            // Link Left
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        }
        else
            break;
    
    leftTreeMax->right = t->left;
    rightTreeMin->left = t->right;
    t->left = header.right;
    t->right = header.left;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Copy and paste you developed methods in q1, update the following two methods
///////////////////////////////////////////////////////////////////////////////////////////////

// Function to insert a new element x in splay tree
template <typename Comparable>
void SplayTree<Comparable>::insert(const Comparable &x)
{
    static BinaryNode *newNode = nullptr;

    if (newNode == nullptr){
        newNode = new BinaryNode;
        newNode->value = 1;
        newNode->element = x;
    }

    if (root == nullNode)
    {
        newNode->left = newNode->right = nullNode;
        root = newNode;
        theSize++;
    }
    else
    {
        splay(x, root);
        if(root->element == x){
            root->value++;
        }
        else if (x < root->element)
        {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullNode;
            root = newNode;
            theSize++;
        }
        else if (root->element < x)
        {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullNode;
            root = newNode;
            theSize++;
        }
        else
        {
            theSize++;
            return;
        }
    }
    newNode = nullptr; // so next insert will call new

}

// The remove function for Splay tree, removing a node with element equal to x.
// Note that this function will update the root of Splay Tree after removing/searching the node
template <typename Comparable>
int SplayTree<Comparable>::remove(const Comparable &x)
{
    // If x is found, it will be splayed to the root by search
    if (!search(x))
        return 0; // Item not found; do nothing

    BinaryNode *newTree;

    if (root->left == nullNode)
        newTree = root->right;
    else
    {
        // Find the maximum in the left subtree
        // Splay it to the root; and then attach right child
        newTree = root->left;
        splay(x, newTree); 
        newTree->right = root->right;
    }
    // Old node's value to be returned
    int oldData = root -> value;

    delete root;
    theSize--;
    root = newTree;

    return oldData;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Complete the szie method
///////////////////////////////////////////////////////////////////////////////////////////////
template <typename Comparable>
int SplayTree<Comparable>::size() const
{
    return theSize;
}
