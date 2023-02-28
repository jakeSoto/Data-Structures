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

int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 01: Q03 ~ Jacob Soto \n" << endl;

    list<int> ogList;
    srand(time(0));

    for(int i = 0; i < 10; i++){
        ogList.push_back(rand() % 100 + 1);
    }
    cout << "Originally created list: ", printList(ogList);

    ogList.sort();
    cout << "\nSorted list: ", printList(ogList);

    ogList.reverse();
    cout << "\nList in descending order: ", printList(ogList);

    cout << "\n--------------------------------------------" << endl;
    return 0;
}
