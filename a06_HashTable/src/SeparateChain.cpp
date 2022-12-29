#include "SeparateChain.h"
using namespace std;

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size) : currentSize{0}
{
    theLists.resize(size);
}

/////////////////////////////////////////////////////////////////////
/**
 * return (input key) % (bucket size)
 */
template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const
{
    return hash(x) % theLists.size();
}

/**
 * A hash routine for ints. Return the key
 */
template <typename HashedObj>
size_t HashTable<HashedObj>::hash(const HashedObj &key) const
{
    return key;
}

/**
 * Insert a node whose id == x (all student information stored
 * in s): if the node is found, do nothing and return false
 * Otherwise, insert the node to the BST tree (including student information
 * stored in s), and return true
 */
template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x, Student<string> &s)
{
    auto &whichList = theLists[myhash(x)];
    if (whichList.contains(x))
        return false;   // Found node in Hash Table BST
    else
        whichList.insert(x, s);     // New node in Hash Table BST
    ++currentSize;
    return true;
}

/**
 * Find whether id == x is in the database, if found, update the student information
 * and return true. Otherwise, return false
 */
template <typename HashedObj>
bool HashTable<HashedObj>::update(const HashedObj &x, Student<string> &s)
{
    bool updated;
    auto &whichList = theLists[myhash(x)];
    updated = whichList.update(x, s);
    printNodeInfo(x);

    if(!updated)
        return false;
    else
        return true;
}

/**
 * Find whether id == x is in the database, if found, remove the node and return true
 * Otherwise, return false
 */
template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x)
{
    auto &whichList = theLists[myhash(x)];
    if(!whichList.contains(x))
        return false;
    
    whichList.remove(x);
    --currentSize;
    return true;
}

/**
 * If the x (student id) is found, print out student information whose id == x
 * return true.
 * Otherwise, print out "x was not found" and return false
 * You should use bool printNodeInfo(const Comparable &x)
 * in BinarySearchTree class
 */
template <typename HashedObj>
bool HashTable<HashedObj>::printNodeInfo(const HashedObj &x)
{
    auto whichList = theLists[myhash(x)];
    return whichList.printNodeInfo(x);
}

/**
 * Display the content of the hash table
 */
template <typename HashedObj>
void HashTable<HashedObj>::displayHash()
{
    for (int i = 0; i < 7; i++)
    {
        cout << i;
        theLists[i].printTree(cout);
        cout << endl;
    }
    cout << "Current size of Hash Table: " << currentSize << endl;
}

/**
 * Make the hash table empty
 */
template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for(auto &thisList : theLists)
        thisList.makeEmpty();
    currentSize = 0;
}