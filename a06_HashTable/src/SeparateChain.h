#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <string>
#include "BinarySearchTree.h"

// SeparateChaining Hash table class
template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101);
    void makeEmpty();
    bool insert(const HashedObj &x, Student<string> &s);
    bool update(const HashedObj &x, Student<string> &s);
    bool remove(const HashedObj &x);
    void displayHash();
    bool printNodeInfo(const HashedObj &x);

private:
    vector<BinarySearchTree<HashedObj>> theLists;
    int currentSize;
    size_t myhash(const HashedObj &x) const;
    size_t hash(const HashedObj &key) const;
};
#endif