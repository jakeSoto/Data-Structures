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
    cout << "IT 279 Assignment 02: Q01 ~ Jacob Soto \n" << endl;

    list<int> myList;
    srand(time(0));
    int temp = 0;

    cout << "The randomly generated numbers: ";
    for(int i = 0; i < 10; i++){
        temp = rand() % 100 + 1;
        myList.push_front(temp);
        cout << temp << " ";
    }cout << endl;
    cout << "Created list: ", printList(myList);

    myList.sort();
    myList.reverse();
    cout << "\nList in descending order: ", printList(myList);

    cout << "\n--------------------------------------------" << endl;
    return 0;
}
