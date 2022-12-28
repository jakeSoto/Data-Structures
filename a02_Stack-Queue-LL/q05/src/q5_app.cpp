#include "SingleList.h"
#include "SingleList.cpp"
#include <iostream>
using namespace std;

int main()
{
    SingleList<int> *lst = new SingleList<int>();
    int val;
    lst->add(10);
    lst->add(12);
    lst->add(15);
    lst->add(6);
    lst->add(3);
    lst->add(8);
    lst->add(3);
    lst->add(6);    
    lst->add(18);
    lst->add(5);
    lst->add(15);

    cout << "\n--------------------------------------------" << endl;
    cout << "IT 279 Assignment 02: Q05 ~ Jacob Soto" << endl;
    cout << "\nThe original linked list: ";
    lst->print();

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            val = 6;
        else if (i == 1)
            val = 28;
        else
            val = 18;

        if (lst->remove(val))
        {
            cout << "Remove " << val << " is successful" << endl;
        }
        else
        {
            cout << "Remove " << val << " is failed" << endl;
        }
    }

    cout << "The updated linked list: ";
    lst->print();
    cout << "The number of nodes in the list: " << lst->size() << endl;
    cout << "--------------------------------------------" << endl
         << endl;

    return 0;
}