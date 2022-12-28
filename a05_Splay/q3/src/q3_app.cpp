#include "SplayTree.h"
#include "flags.h"
#include "SplayTree.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <map>
using namespace std;


// Testing program
int main()
{
    cout << "\nAssignment 05, Question 03 ~ Jacob Soto: " << endl;
    SplayTree<string> t;
    list< pair< int, string > > theList;
    map<string, int> theMap;
    string line;
    int i = 0;
    
    ifstream myFile;

    if(TEST0)
    {
    // Creating splay tree
        myFile.open("enroll.txt");
        if(myFile.is_open())
        {
            while(getline (myFile, line))
                t.insert(line);
        }
        myFile.close();

        // Printing splay tree
        cout << "The initial splay tree is: " << endl;
        t.printTree();
        cout << "\n" << endl;


    // Creating list
        myFile.open("query.txt");
        if(myFile.is_open())
        {
            while(getline (myFile, line))
            {
                if(t.search(line))
                {
                    i = t.remove(line);
                    theList.push_back(make_pair(i, line));
                    while(i != 0)
                    {
                        t.insert(line);
                        i--;
                    }
                }
                else
                    theList.push_back(make_pair(0, line));
            }
        }
        myFile.close();

        // Sorting list in descending order
        theList.sort();
        theList.reverse();

        // Printing list
        cout << "The initial sorted list is: " << endl;
        for(const auto& itr : theList)
            cout << "(" << itr.second << ", " << itr.first << ")  ";
        cout << "\n" << endl;


    // Creating map
        myFile.open("query.txt");
        if(myFile.is_open())
        {
            while(getline (myFile, line))
            {
                if(t.search(line))
                    theMap.insert(pair<string, int>(line, t.remove(line)));
                else
                    theMap.insert({line, 0});
            }
            
            myFile.close();
        }

        // Printing map
        cout << "The initial map is: " << endl;
        for(auto itr = theMap.begin(); itr != theMap.end(); ++itr)
            cout << "(" << itr->first << ", " << itr->second << ")  ";
        cout << "\n" << endl;


        cout << "The updated splay tree is: " << endl;
        t.printTree();
        cout << "\n" << endl;

    }

    return 0;
}

