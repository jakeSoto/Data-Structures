#include "AvlTree.h"
#include "flags.h"
#include "AvlTree.cpp"
#include <iostream>

using namespace std;

// Testing program
int main()
{
    AvlTree<int> t;

    if (TEST0)
    {
        cout << "Assignment 04, Question 01 ~ Jacob Soto: " << endl;
        cout << "Test0: " << endl;
        t.insert(50);
        t.insert(30);
        t.insert(40);

        t.insert(35);
        t.insert(32);

        t.insert(40);
        t.insert(45);
        t.insert(48);

        t.insert(46);
        t.insert(30);
        t.insert(47);

        cout << "The built AVL tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;

        t.remove(48);
        cout << "The updated AVL tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;
    }
    if (TEST1)
    {
        cout << "Assignment 04, Question 02 ~ Jacob Soto: " << endl;
        cout << "Test1: " << endl;
        t.insertImproved(50);
        t.insertImproved(30);
        t.insertImproved(40);

        t.insertImproved(35);
        t.insertImproved(32);

        t.insertImproved(40);
        t.insertImproved(45);
        t.insertImproved(48);

        t.insertImproved(46);
        t.insertImproved(30);
        t.insertImproved(47);

        cout << "The built AVL tree is (preorder traversal) using continuous rotations:" << endl;
        t.printTree();
        cout << endl;

        t.removeImproved(48);
        cout << "The updated AVL tree is (preorder traversal):" << endl;
        t.printTree();
        cout << endl;
    }

    // You need to test three times, and output the results
    if (TEST2)
    {
        cout << "Assignment 04, Question 03 ~ Jacob Soto: " << endl;
        cout << "Test2: " << endl;
        cout << "The generated random AVL tree:" << endl;
        t.makeRandomTree(3, 16);
        t.printTree();
        cout << endl;
    }

    return 0;
}