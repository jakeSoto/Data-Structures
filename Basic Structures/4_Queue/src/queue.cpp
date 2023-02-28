#include <iostream>
#include <queue>
using namespace std;


int removeSecond(queue<int> *pQueue)
{
    int temp = pQueue -> front();
    pQueue -> pop();
    int secondVal = pQueue -> front();
    pQueue -> pop();
    pQueue -> push(temp);

    for(int i = 0; i < 6; ++i){
        pQueue -> push(pQueue -> front());
        pQueue -> pop();
    }

    return secondVal;
}


int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 02: Q04 ~ Jacob Soto \n" << endl;

    queue<int> myQueue;
    int sum = 0;
    srand(time(0));


    cout << "The randomly generated numbers: ";
    for (int i = 0; i < 8; i++){
        int temp = rand() % 50 + 1;
        myQueue.push(temp);
        cout << temp << " ";
    }cout << endl;
    
    int secondVal = removeSecond(&myQueue);

    cout << "Removed node: " << secondVal << endl;


    cout << "Updatd Queue: ";
    while (!myQueue.empty())
    {
        if(myQueue.front() % 2 != 0){
            sum += myQueue.front();
        }
        cout << ' ' << myQueue.front();
        myQueue.pop();
    }


    cout << "\nSum of the odd values: " << sum << endl;

    cout << "\n--------------------------------------------" << endl;
    return 0;
}