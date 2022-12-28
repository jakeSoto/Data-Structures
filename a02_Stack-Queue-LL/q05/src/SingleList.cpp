#include "SingleList.h"
#include <algorithm>

template <typename Object>
SingleList<Object>::SingleList()
{
    init();
}

template <typename Object>
SingleList<Object>::~SingleList() { eraseList(head); }

template <typename Object>
SingleList<Object>::SingleList(const SingleList &rhs)
{
    eraseList(head);
    init();
    *this = rhs;
}

template <typename Object>
void SingleList<Object>::init()
{
    theSize = 0;
    head = new Node;
    head->next = (Object)NULL;
}

template <typename Object>
void SingleList<Object>::eraseList(Node *h)
{
    Node *ptr = h;
    Node *nextPtr;

    while (ptr != (Object)NULL)
    {
        nextPtr = ptr->next;
        delete ptr;
        ptr = nextPtr;
    }
}

template <typename Object>
void SingleList<Object>::print()
{
    Node *ptr = head->next;
    while (ptr != (Object)NULL)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

// Methods/functions for assignment 02: q5
template <typename Object>
bool SingleList<Object>::contains(const Object &x)
{
    Node *temp = head;
    while(temp != NULL){
        if(temp -> data == x){
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

template <typename Object>
bool SingleList<Object>::add(Object x)
{
    Node *temp = new Node(x);
    temp->next = head;
    head = temp;

    return true;
}

template <typename Object>
bool SingleList<Object>::remove(Object x)
{
    Node *temp = head;
    Node *prev = head;

    if(head != NULL){
        if(head -> data == x) {
            head = head -> next;
            return true;
        }
    }
    while(temp != NULL){
        if(temp -> data == x){
            prev -> next = temp -> next;
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

template <typename Object>
int SingleList<Object>::size()
{
    int N = 0;
    Node *temp = head;
    while(temp != NULL){
        temp = temp -> next;
        N++;
    }
    return N - 1;
}
