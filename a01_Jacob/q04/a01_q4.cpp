#include <iostream>
#include <list>
using namespace std;

template <typename Object>
void printList(list<Object> pList)
{
    for (auto const &v : pList)
    {
        cout << v << " ";
    }
}

template <typename Object>
Object removeSmallest(list<Object> *ls){
    list<int>::iterator smallest = ls->begin();
    list<int>::iterator compareTo = ls->begin();
    compareTo++;
    
    while(compareTo != ls->end()){
        if(*compareTo < *smallest){
            smallest = compareTo;
        }
        compareTo++;
    }

    ls->remove(*smallest);
    return *smallest;
}

int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 01: Q04 ~ Jacob Soto \n" << endl;

    list<int> ogList;
    int smallestVal;
    list<int>::iterator it;

    ogList.push_back(45), ogList.push_back(25), ogList.push_back(35), ogList.push_back(10), ogList.push_back(20), ogList.push_back(30), ogList.push_back(20), ogList.push_back(10);
    cout << "Originally created list: ", printList(ogList);

    smallestVal = removeSmallest(&ogList);
    cout << "\nSmallest value: " << smallestVal << endl;
    cout << "List after removing the smallest value: ", printList(ogList);


    cout << "\n--------------------------------------------" << endl;
    return 0;
}
