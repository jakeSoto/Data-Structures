#include "List.h"
#include "List.cpp"
#include <iostream>
using namespace std;

template <typename Object>
void printList(List<Object> pList)
{
    typename List<Object>::const_iterator pIter;
    for (pIter = pList.begin(); pIter != pList.end(); pIter++)
    {
        cout << *pIter << " ";
    }
}

int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 01: Q01 ~ Jacob Soto \n" << endl;

    List<int> pList;
    List<int>::iterator it;

    pList.push_back(2), pList.push_back(4), pList.push_back(5), pList.push_back(7), pList.push_back(8), pList.push_back(1), pList.push_back(7), pList.push_back(15);
    cout << "The created list is: ", printList(pList);

    it = pList.find(pList.begin(), pList.end(), 7);
    cout << "\nThe found node value pointed by iterator is: " << *it << endl;

    cout << "The following node values in the list after the found node: ";
    it++;
    while(it != pList.end())
    {
        cout << *it << " ";
        it++;
    }


    cout << "\n--------------------------------------------" << endl;
    return 0;
}
