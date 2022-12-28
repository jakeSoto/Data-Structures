#ifndef SINGLELIST_H
#define SINGLELIST_H
#include <iostream>
using namespace std;

template <typename Object>
class SingleList
{
private:
    struct Node
    {
        Object data;
        Node *next;
        Node(const Object &d = Object(), Node *n = (Object)NULL) : data(d), next(n) {}
    };

public:
    SingleList();
    ~SingleList();
    SingleList(const SingleList &rhs);

    void init();
    void eraseList(Node *h);
    void print();

    // Methods/functions for assignment 02: q5
    bool contains(const Object &x);
    bool add(Object x);
    bool remove(Object x);
    int size();

private:
    Node *head;
    int theSize;
};
#endif