#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename Object>
void printVector(vector<Object> pVect)
{
    for (auto const &v : pVect)
    {
        cout << v << " ";
    }
}


template <typename Object>
int sumOddNums(vector<Object> pVect)
{
    int sum = 0;

    for (auto const &v : pVect)
    {
        if(v % 2 != 0){
            sum += v;
        }
    }
    return sum;
}

int main()
{
    cout << "--------------------------------------------" << endl;
    cout << "IT 279 Assignment 02: Q02 ~ Jacob Soto \n" << endl;

    vector<int> myVect;
    srand(time(0));

    for(int i = 0; i < 12; i++){
        myVect.push_back(rand() % 100 + 1);
    }
    cout << "Created vector: ", printVector(myVect); cout << endl;

    reverse(myVect.begin() + 6, myVect.end());
    cout << "Vector reversed from [6] to the end: ", printVector(myVect); cout << endl;

    cout << "Sum of odd elements: " << sumOddNums(myVect) << endl;

    myVect.erase(myVect.begin() + 6, myVect.begin() + 9);
    cout << "Vector after removing elements [6] -> [8]:\n", printVector(myVect); cout << endl;


    cout << "\n--------------------------------------------" << endl;
    return 0;
}