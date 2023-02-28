#include "AVL.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename Comparable>
AvlTree<Comparable>::AvlTree() : root{nullptr}
{
}

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
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <typename Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

/**
 * Print the tree contents in sorted order.
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
 * Make the tree logically empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template <typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlTree<Comparable>::AvlNode *&t)
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
 * Internal method to print a subtree rooted at t in sorted order.
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

// Get Balance factor of node N
template <typename Comparable>
int AvlTree<Comparable>::getBalance(AvlNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax() const
{
    if (isEmpty()){
        cout << "\nCannot find the node" << endl;
        throw UnderflowException{};
    }
    return findMax(root);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax(AvlNode *t) const
{
    if (t != nullptr){
        while (t -> right != nullptr){
            t = t -> right;
        }
    }
    return t;
}

/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin() const
{
    if (isEmpty())
    {
        cout << "\nCannot find the node" << endl;
        throw UnderflowException{};
    }
    return findMin(root);
}
/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin(AvlNode *t) const
{
    if (t != nullptr){
        while (t -> left != nullptr){
            t = t -> left;
        }
    }
    return t;
}

template <typename Comparable>
void AvlTree<Comparable>::rightRotate(AvlNode *&y)
{
    AvlNode *x = y -> left;
    AvlNode *T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    y -> height = max(height(y->left), height(y->right)) + 1;
    x -> height = max(height(x->left), height(x->right)) + 1;

    y = x;
}

template <typename Comparable>
void AvlTree<Comparable>::leftRotate(AvlNode *&y)
{
    AvlNode *x = y -> right;
    AvlNode *T2 = x -> left;

    x -> left = y;
    y -> right = T2;

    y -> height = max(height(y->left), height(y->right)) + 1;
    x -> height = max(height(x->left), height(x->right)) + 1;

    y = x;
}


static const int ALLOWED_IMBALANCE = 1;
template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode *&y)
{
    if(y == nullptr)
        return;
    if(height(y->left) - height(y->right) > ALLOWED_IMBALANCE){
        if(height(y->left->left) >= height(y->left->right))
            rightRotate(y);
        else{
            leftRotate(y->left);
            rightRotate(y);
        }
    }
    else if(height(y->right) - height(y->left) > ALLOWED_IMBALANCE){
        if(height(y->right->right) >= height(y->right->left))
            leftRotate(y);
        else{
            rightRotate(y->right);
            leftRotate(y);
        }
    }

    y->height = max(height(y->left), height(y->right)) + 1;
}

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x)
{
    insert(x, root);
}


template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t)
{
    if(t == nullptr)
        t = new AvlNode{x, nullptr, nullptr};
    else if(x < t->element)
        insert(x, t->left);
    else if(t->element < x)
        insert(x, t->right);
    else
        return; // Duplicate value
    
    balance(t);
}


template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x)
{
    remove(x, root);
}


template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlNode *&t)
{
    if(t == nullptr)
        return;

    if(x < t->element)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr){  //Two children are intialized
        t->element = findMin(t->right) -> element;
        remove(t->element, t->right);
    }else{
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    balance(t);
}


// d)	(40 pts) Complete balance method, must have the function of outputting each of the four cases to handle unbalance and the node that is used as root to rotate. For example:

// left left case: rightRotate (50)
// left left case: rightRotate (20)
// left right case: leftRotate (40), rightRotate(50)

// right left case: rightRotate (50), leftRotate(45)

// e)	(10 pts) Complete insert method 
// f)	(10 pts) Complete remove method
