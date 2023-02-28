#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <sstream> // std::stringstream

#include "BinarySearchTree.cpp"
#include "SeparateChain.cpp"
#include "Student.cpp"

using namespace std;

template <typename Comparable>
void readToHashTable(string str, HashTable<Comparable> &h);
template <typename Comparable>
void searchHashTree(string str, HashTable<Comparable> &h);
template <typename Comparable>
void updateHashTree(string str, HashTable<Comparable> &h);
template <typename Comparable>
void removeFromHashTree(string str, HashTable<Comparable> &h);

int main()
{
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Assignment 06 ~ Jacob Soto" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    HashTable<int> h(7);

    cout << "Initial Hash Table (implemented using a BST, printed with inorder traversal): " << endl;
    readToHashTable("enroll_assg.txt", h);
    h.displayHash();
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    
    cout << "Search Test 1: " << endl;
    cout << "Students whose records were searched: " << endl;
    searchHashTree("search_assg1.txt", h);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    
    cout << "Search Test 2: " << endl;
    cout << "Students whose records were searched: " << endl;
    searchHashTree("search_assg2.txt", h);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    
    cout << "Update Test: " << endl;
    cout << "Students whose records have been updated: " << endl;
    updateHashTree("update_assg.txt", h);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    
    cout << "Remove Test: " << endl;
    cout << "Students whose records have been removed: " << endl;
    removeFromHashTree("remove_assg.txt", h);
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Updated Hash Table (implemented using a BST, printed with inorder traversal): " << endl;
    h.displayHash();
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    cout << "The updated Hash Table after empty operation: " << endl;
    h.makeEmpty();
    h.displayHash();
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    return 0;
}


template <typename Comparable>
void readToHashTable(string str, HashTable<Comparable> &h){
    Student<string> s;
    string line, stuID, fName, lName, dept, grade;
    ifstream myFile;

    myFile.open(str);
    if(myFile.is_open())
    {
        while(getline(myFile, line))
        {
            stringstream iss(line);
            iss >> stuID;
            iss >> fName, s.setFirstName(fName);
            iss >> lName, s.setLastName(lName);
            iss >> dept, s.setDepartment(dept);
            iss >> grade, s.setGPA(grade);

            h.insert(stoi(stuID), s);
        }
    }
    myFile.close();
}

template <typename Comparable>
void searchHashTree(string str, HashTable<Comparable> &h){
    string line = "";
    ifstream myFile;

    myFile.open(str);
    if(myFile.is_open())
    {
        while(getline(myFile, line))
            h.printNodeInfo(stoi(line));
    }
    myFile.close();
}

template <typename Comparable>
void updateHashTree(string str, HashTable<Comparable> &h){
    Student<string> s;
    string line, stuID, fName, lName, dept, grade;
    ifstream myFile;

    myFile.open(str);
    if(myFile.is_open())
    {
        while(getline(myFile, line))
        {
            stringstream iss(line);
            iss >> stuID;
            iss >> fName, s.setFirstName(fName);
            iss >> lName, s.setLastName(lName);
            iss >> dept, s.setDepartment(dept);
            iss >> grade, s.setGPA(grade);

            h.update(stoi(stuID), s);
        }
    }
    myFile.close();
}

template <typename Comparable>
void removeFromHashTree(string str, HashTable<Comparable> &h){
    string line = "";
    ifstream myFile;

    myFile.open(str);
    if(myFile.is_open())
    {
        while(getline(myFile, line)){
            h.printNodeInfo(stoi(line));
            h.remove(stoi(line));
        }
    }
    myFile.close();
}