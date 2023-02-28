#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include "Student.h"
using namespace std;

// BinarySearchTree class
template <typename Comparable>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        Comparable element; 
        Student<string> val;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, Student<string> &theVal, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, val{theVal}, left{lt}, right{rt}
        {
            val.setFirstName(theVal.getFirstName());
            val.setLastName(theVal.getLastName());
            val.setDepartment(theVal.getDepartment());
            val.setGPA(theVal.getGPA());
        }
    };

    BinaryNode *root;
    BinaryNode *clone(BinaryNode *t) const;
    void makeEmpty(BinaryNode *&t) const;

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs); // Copy constructor
    BinarySearchTree(BinarySearchTree &&rhs);      // Move constructor
    ~BinarySearchTree();                           // Destructor for the tree

    // Copy assignment
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move assignment
    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    bool isEmpty() const;
    void makeEmpty();

    // Assignment 04
private:
    BinaryNode *findMin(BinaryNode *t) const;
    BinaryNode *findMax(BinaryNode *t) const;

    bool contains(const Comparable &x, BinaryNode *t) const;
    void insert(const Comparable &x, Student<string> &val, BinaryNode *&t);
    void remove(const Comparable &x, BinaryNode *&t);    
    
    bool update(const Comparable &x, Student<string> &val, BinaryNode *&t);
    bool printNodeInfo(const Comparable &x, BinaryNode *t) const;
    void printTree(BinaryNode *t, ostream &out);    

public:
    BinaryNode *findMin() const;
    BinaryNode *findMax() const;

    bool contains(const Comparable &x) const;
    void insert(const Comparable &x, Student<string> &val);  
    void remove(const Comparable &x);

    bool update(const Comparable &x, Student<string> &val);
    bool printNodeInfo(const Comparable &x) const;
    void printTree(ostream &out = cout);
};
#endif
