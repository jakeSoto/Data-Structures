#include "AvlTree.h"
#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in pre-order
// ******************ERRORS********************************
// Throws UnderflowException as warranted
template <typename Comparable>
AvlTree<Comparable>::AvlTree() : root{nullptr} {}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree &rhs) : root{nullptr}
{
    root = clone(rhs.root);
}
template <typename Comparable>
AvlTree<Comparable>::AvlTree(AvlTree &&rhs) : root{rhs.root}
{
    rhs.root = nullptr;
}
template <typename Comparable>
AvlTree<Comparable>::~AvlTree()
{
    makeEmpty();
}

/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
const Comparable &AvlTree<Comparable>::findMin() const
{
    if (isEmpty())
        throw UnderflowException{};
    return findMin(root)->element;
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
const Comparable &AvlTree<Comparable>::findMax() const
{
    if (isEmpty())
        throw UnderflowException{};
    return findMax(root)->element;
}
/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <typename Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}
/**
 * Make the tree logically empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}
/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin(AvlNode *t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax(AvlNode *t) const
{
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}
/**
 * Internal method to make subtree empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}
/**
 * Internal method to clone subtree.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::clone(AvlNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
}
// Avl manipulations
/**
 * Return the height of node t or -1 if nullptr.
 */
template <typename Comparable>
int AvlTree<Comparable>::height(AvlNode *t) const
{
    return t == nullptr ? -1 : t->height;
}
template <typename Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
    return lhs > rhs ? lhs : rhs;
}
/**
 * Returns true if x is found in the tree.
 */
template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable &x) const
{
    return contains(x, root);
}
/**
 * Internal method to test if an item is in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 */
template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable &x, AvlNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true; // Match
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Methods for assignment 03: Q1
/**
 * Print the tree contents in pre-order.
 */
template <typename Comparable>
void AvlTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);

}
/**
 * Internal method to print a subtree rooted at t in pre-order.
 */
template <typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode *t) const
{
    if (t != nullptr)
    {
        cout << t->element << "  ";
        printTree(t->left);
        printTree(t->right);
    }
}
/**
 * Insert x into the tree; duplicates are ignored.
 */
template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x)
{
    if(contains(x))
        return; // Value is already in tree
    else
        insert(x, root);
}
/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t)
{
    if(t == nullptr)
        t = new AvlNode{x, nullptr, nullptr};
    else if(x < t->element)
        insert(x, t->left);
    else if(t->element < x)
        insert(x, t->right);
    
    balance(t);
}

/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x)
{
    if(contains(x))
        remove(x, root);
    else
        return;
}
/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlNode *&t)
{
    if(x < t->element)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr)  //Two children are intialized
    {    
        t->element = findMax(t->left) -> element;
        remove(t->element, t->left);
        cout << "\nRemoved the maximum node of left sub-tree" << endl;
    }
    else
    {
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    balance(t);
}

/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
template <typename Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode *&k2)
{
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
template <typename Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode *&k1)
{
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}
/**
 * Double rotate binary tree node: first left child.
 * with its right child; then node k3 with new left child.
 * For AVL trees, this is a double rotation for case 2.
 * Update heights, then set new root.
 */
template <typename Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode *&k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
template <typename Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode *&k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}


static const int ALLOWED_IMBALANCE = 1;
// Assume t is balanced or within one of being balanced
template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode *&t)
{
    if(t == nullptr)
        return;
    
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
    {
        if(height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
    {
        if(height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Methods for assignment 03: Q2
// Write the functions to perform the double rotation without the inefficiency of doing
// two single rotations: you cannot use rotateWithLeftChild and rotateWithRightChild
// in the implementation
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::doubleRotateWithLeftChild(AvlNode *k3)
{
    AvlNode *k1 = k3->left;
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k3->left = k2->right;
    k2->left = k1;
    k2->right = k3;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k3->height = max(height(k3->left), height(k3->right)) + 1;
    k2->height = max(height(k1), height(k3)) + 1;
    k3 = k2;
    return k3;
}
// Write the functions to perform the double rotation without the inefficiency of doing
// two single rotations: you cannot use rotateWithLeftChild and rotateWithRightChild
// in the implementation
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::doubleRotateWithRightChild(AvlNode *k1)
{
    AvlNode *k3 = k1->right;
    AvlNode *k2 = k3->left;
    k3->left = k2->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->right = k3;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k3->height = max(height(k3->left), height(k3->right)) + 1;
    k2->height = max(height(k1), height(k3)) + 1;
    k1 = k2;
    return k1;
}

// Assume t is balanced or within one of being balanced
// You must use the developed doubleRotateWithLeftChild and doubleRotateWithRightChild for double rotation
// You can use rotateWithLeftChild and rotateWithRightChild for single rotation
template <typename Comparable>
void AvlTree<Comparable>::balanceImproved(AvlNode *&t)
{
    if(t == nullptr)
        return;
    
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
    {
        if(height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            t = doubleRotateWithLeftChild(t);
    }
    else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
    {
        if(height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            t = doubleRotateWithRightChild(t);
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void AvlTree<Comparable>::insertImproved(const Comparable &x, AvlNode *&t)
{
    if(t == nullptr)
        t = new AvlNode{x, nullptr, nullptr};
    else if(x < t->element)
        insertImproved(x, t->left);
    else if(t->element < x)
        insertImproved(x, t->right);

    balanceImproved(t);
}
/**
 * Insert x into the tree; duplicates are ignored.
 */
template <typename Comparable>
void AvlTree<Comparable>::insertImproved(const Comparable &x)
{
    if(contains(x))
        return;
    else
        insertImproved(x, root);
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void AvlTree<Comparable>::removeImproved(const Comparable &x, AvlNode *&t)
{
    if(x < t->element)
        removeImproved(x, t->left);
    else if(t->element < x)
        removeImproved(x, t->right);
    else if(t->left != nullptr && t->right != nullptr)  //Two children are intialized
    {    
        t->element = findMax(t->left) -> element;
        removeImproved(t->element, t->left);
        cout << "\nRemoved the maximum node of left sub-tree" << endl;
    }
    else
    {
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    balanceImproved(t);
}

/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <typename Comparable>
void AvlTree<Comparable>::removeImproved(const Comparable &x)
{
    if(contains(x))
        removeImproved(x, root);
    else
        return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Methods for assignment 04: Q3
// Create an Avl tree using the generated random number (integer) between lower and upper inclusive
template <typename Comparable>
void AvlTree<Comparable>::makeRandomTree(const Comparable lower, const Comparable upper)
{
    int N = (upper - lower) + 1;
    int randNum = -1;
    srand(time(0));

    for(int i = 0; i < N; i++){
        randNum = (rand() % N) + lower;
        while(contains(randNum))
            randNum = (rand() % N) + lower;
        insert(randNum);
    }
}
