#include <iostream>
#include <stack>
using namespace std;


int removeSecond(stack<int> *pStack)
{
    int temp = pStack -> top();
    pStack -> pop();
    int secondVal = pStack -> top();
    pStack -> pop();
    pStack -> push(temp);

    return secondVal;
}


int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 02: Q03 ~ Jacob Soto \n" << endl;

    stack<int> myStack;
    int arr[8];
    int sum = 0;
    srand(time(0));


    cout << "The randomly generated numbers: ";
    for (int i = 0; i < 8; i++){
        arr[i] = rand() % 100 + 1;
        myStack.push(arr[i]);
        sum += arr[i];
        cout << arr[i] << " ";
    }cout << endl;
    
    int secondVal = removeSecond(&myStack);
    sum -= secondVal;

    cout << "Removed node: " << secondVal << endl;

    cout << "Updated Stack: ";
    while (!myStack.empty())
    {
        cout << ' ' << myStack.top();
        myStack.pop();
    }

    cout << "\nSum of stack: " << sum << endl;

    cout << "\n--------------------------------------------" << endl;
    return 0;
}