//Name: David Schurer
//Class: CSS 342
//Assignment 4: Skiplist
#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <climits>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class SNode {

public:
    // SNode stores int as data
    explicit SNode(int data);

    // data for SNode
    int data;

    // link to next SNode
    SNode* next;

    // link to prev SNode
    SNode* prev;

    // link to up one level
    SNode* upLevel;

    // link to down one level
    SNode* downLevel;

};

class SkipList {

public:
    // default SkipList has depth of 1, just one doubly-linked list
    explicit SkipList(int depth);

    // destructor
    virtual ~SkipList();

    // return true if successfully added, no duplicates
    bool Add(int data);

    // return true if successfully removed
    bool Remove(int data);

    // return true if found in SkipList
    bool Contains(int data);

    // given a SNode, place it before the given NextNode
    void addBefore(SNode* newNode, SNode* nextNode);

    // return true 50% of the time
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

    // The friend function is used to display all the elements of the SkipList
    friend ostream& operator<<(ostream& os, const SkipList& list);

private:
    // depth of SkipList, levels are 0 to depth-1
    int depth;

    // Array of depth SNode* objects as frontGuards linking levels
    // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
    SNode** frontGuards;

    // Array of depth Snode* objects as rearGuards linking levels
    SNode** rearGuards;

    // The levels vector is used to store the depth (# of levels) in the SkipList
    vector<SNode*> levels;

};

#endif
