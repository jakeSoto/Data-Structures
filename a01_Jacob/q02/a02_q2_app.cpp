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

// Assumes both input lists are sorted
template <typename Object>
List<Object> listUnion(const List<Object> &L1, const List<Object> &L2)
{
    List<Object> L3;
    typename List<Object>::const_iterator iterL1 = L1.begin();
    typename List<Object>::const_iterator iterL2 = L2.begin();

    while (iterL1 != L1.end() && iterL2 != L2.end()){
        if(*iterL1 == *iterL2){
            L3.push_back(*iterL1);
            iterL1++;
            iterL2++;
        }
        else if(*iterL1 < *iterL2){
            L3.push_back(*iterL1);
            iterL1++;
        }
        else{
            L3.push_back(*iterL2);
            iterL2++;
        }
    }
    
   while (iterL1 != L1.end())
    {
        L3.push_back(*iterL1);
        iterL1++;
    }

    while (iterL2 != L2.end()){
        L3.push_back(*iterL2);
        iterL2++;
    }
    
    return L3;
}

// Assumes both input lists are sorted
// This function is used as a reference
template <typename Object>
List<Object> intersection(const List<Object> &L1, const List<Object> &L2)
{
    List<Object> intersect;
    typename List<Object>::const_iterator iterL1 = L1.begin();
    typename List<Object>::const_iterator iterL2 = L2.begin();

    while (iterL1 != L1.end() && iterL2 != L2.end())
    {
        if (*iterL1 == *iterL2)
        {
            intersect.push_back(*iterL1);
            iterL1++;
            iterL2++;
        }
        else if (*iterL1 < *iterL2)
            iterL1++;
        else
            iterL2++;
    }
    return intersect;
}

int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 01: Q02 ~ Jacob Soto" << endl;

    List<int> L1;
    List<int> L2;
    List<int> L3;

    L1.push_back(2), L1.push_back(4), L1.push_back(5), L1.push_back(7), L1.push_back(8), L1.push_back(15);

    L2.push_back(1), L2.push_back(4), L2.push_back(6), L2.push_back(7);

    cout << "The first created list L1: ", printList(L1);
    cout << "\nThe second created List L2: ", printList(L2);

    L3 = listUnion(L1, L2);
    cout << "\nThe union list: ", printList(L3);


  
    cout << "\n--------------------------------------------" << endl;
    return 0;
}
