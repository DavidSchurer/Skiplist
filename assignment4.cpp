//Name: David Schurer
//Class: CSS 342
//Assignment 4: Skiplist
#include <iostream>
#include <vector>
#include <climits>
#include <random>
#include <cstdlib>
#include <ctime>
#include "skiplist.h"
using namespace std;

// SkipList constructor will initialize all of the levels in the SkipList as well as the rearGuards and frontGuards for each level and link them together
SkipList::SkipList(int depth) {

    srand(time(NULL));

    // Allocating memory for two arrays of SNode pointers that will represent the frontGuards and rearGuards in the SkipList
    // Each array has a max size of the depth of the SkipList
    frontGuards = new SNode * [depth];
    rearGuards = new SNode * [depth];

    // The frontGuards and rearGuards are initialized for the first level of the SkipList, their data stores the min and max values for integers
    frontGuards[0] = new SNode(INT_MIN);
    rearGuards[0] = new SNode(INT_MAX);

    // The frontGuards and rearGuards for the first level are linked together
    frontGuards[0]->next = rearGuards[0];
    rearGuards[0]->prev = frontGuards[0];

    // This for loop initializes all of the levels of the SkipList with each front and read guard at each level
    for (int i = 1; i < depth; i++) {

        frontGuards[i] = new SNode(INT_MIN);
        rearGuards[i] = new SNode(INT_MAX);

        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->prev = frontGuards[i];

        // While the level is above 0 in the SkipList, each front and rear guard will be connected
        // to the front and rear guards above and below them
        frontGuards[i]->downLevel = frontGuards[i - 1];
        rearGuards[i]->downLevel = rearGuards[i - 1];
        frontGuards[i - 1]->upLevel = frontGuards[i];
        rearGuards[i - 1]->upLevel = rearGuards[i];

    }
    // The vector levels will store the SNode pointers for each level
    levels = vector<SNode*>(depth);

    for (int i = 0; i < depth; i++) {
        levels[i] = frontGuards[i];
    }

    this->depth = depth;
}

// SNode constructor initializes a new node with its given int data
// and sets all of its pointers to null
SNode::SNode(int data) {

    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->upLevel = nullptr;
    this->downLevel = nullptr;

}

// The SkipList destructor frees up any dynamically allocated memory
// by deleting all of the nodes in the SkipList
SkipList::~SkipList() {

    // Start at the first level in the SkipList and iterates until the highest level has been reached
    for (int i = 0; i < depth; i++) {

        // Start at the node that the frontGuard points to
        SNode* currentNode = frontGuards[i]->next;

        // Traverse through the list, deleting each node until rearGuard is reached
        while (currentNode != rearGuards[i]) {
            SNode* tempNode = currentNode;
            currentNode = currentNode->next;
            delete tempNode;
        }
        // Delete the rearGuards and frontGuards for each level
        delete rearGuards[i];
        delete frontGuards[i];
    }
    // Delete the rearGuards and frontGuards arrays
    delete[] rearGuards;
    delete[] frontGuards;

}

// The add method will create a new node with the given data and insert
// it into the SkipList, each node that is added will have a 50% chance of
// being inserted at a higher level 
bool SkipList::Add(int data) {

    SNode* newNode = new SNode(data);
    SNode* nextNode = frontGuards[0]->next;
    SNode* previousNode = frontGuards[0];

    int currentLevel = 0;

    // As long as the data in the next node is smaller than the data we want to insert
    // keep traversing
    while (nextNode->data < data) {
        previousNode = nextNode;
        nextNode = nextNode->next;
    }

    // If the data we want to insert is already in the SkipList, update
    // the next node to contain that data and delete the new node
    if (nextNode->data == data) {

        nextNode->data = data;
        delete newNode;
        return false; // We return false because we did not add data (no duplicates allowed)

    }

    // Call the addBefore method to insert the new node before the next node at the first level
    addBefore(newNode, nextNode);

    // 50% chance to determine whether the node will be inserted at a higher level
    while (alsoHigher() && currentLevel < depth - 1) {
        currentLevel++;

        // Move up one level
        while (previousNode->upLevel == nullptr) {
            previousNode = previousNode->prev;
        }
        previousNode = previousNode->upLevel;

        // New node is created to be inserted in the upper level
        SNode* newUpperNode = new SNode(data);

        // The new node will be inserted before the next node in the upper level
        addBefore(newUpperNode, previousNode->next);

        // The new node now links to its corresponding node below it in the lower level
        newUpperNode->downLevel = newNode;
        newNode->upLevel = newUpperNode;
        // The upper node is now set to new node so that we can add more levels to it
        newNode = newUpperNode;

    }
    // Returns true if the data was added
    return true;
}

// The remove method will start at the top of the SkipList and traverse through each level checking for the data
// to remove, it will ensure that the data is removed at each level that it is found in the SkipList
bool SkipList::Remove(int data) {

    // Initialize currentNode pointer to start at the frontGuard of the top level of the SkipList
    SNode* currentNode = frontGuards[depth - 1];

    // Keep iterating while the currentNode is not a nullptr
    while (currentNode != nullptr) {
        // If the next node's data is equal to the data we are looking for
        if (currentNode->next->data == data) {
            // Remove this node that contains the data we are looking for
            SNode* deleteNode = currentNode->next;
            currentNode->next = deleteNode->next;
            deleteNode->next->prev = currentNode;
            delete deleteNode;

            // If the currentNode is not at the first level of the skipList, it will traverse down one level
            if (currentNode->downLevel != nullptr) {
                currentNode = currentNode->downLevel;
                continue;
            }
            return true;

            // If the currentNode is not at the first level and the next node's data is greater than the data to be removed, go down a level
        }
        else if ((currentNode->downLevel != nullptr) && (currentNode->next->data > data)) {
            currentNode = currentNode->downLevel;

            // If the currentNode is at the first level and the next node's data is greater than the data to be removed, then that data was not found in the SkipList
        }
        else if ((currentNode->downLevel == nullptr) && (currentNode->next->data > data)) {
            return false;

            // Else the current node will keep traversing to the next node in the current level
        }
        else {
            currentNode = currentNode->next;
        }

    }
    return false;
}

// The contains method starts at the top of the SkipList and traverses through each level checking
// if the data that we are looking for is in the SkipList
bool SkipList::Contains(int data) {

    // Initialize currentNode pointer to start at the frontGuard of the top level of the SkipList
    SNode* currentNode = frontGuards[depth - 1];

    // Keep iterating while the currentNode is not a nullptr
    while (currentNode != nullptr) {
        // If the next node's data is equal to the data we are looking for
        if (currentNode->next->data == data) {
            return true;

            // If the currentNode is not at the first level of the skipList, it will traverse down one level
            if (currentNode->downLevel != nullptr) {
                currentNode = currentNode->downLevel;
                continue;
            }
            return true;

            // If the currentNode is not at the first level and the next node's data is greater than the data we are looking for, go down a level
        }
        else if ((currentNode->downLevel != nullptr) && (currentNode->next->data > data)) {
            currentNode = currentNode->downLevel;

            // If the currentNode is at the first level and the next node's data is greater than the data we are looking for, then that data was not found in the SkipList
        }
        else if ((currentNode->downLevel == nullptr) && (currentNode->next->data > data)) {
            return false;

            // Else the current node will keep traversing to the next node in the current level
        }
        else {
            currentNode = currentNode->next;
        }

    }
    return false;

}

// The addBefore method inserts a new node before the nextNode at the current
// level of the SkipList
void SkipList::addBefore(SNode* newNode, SNode* nextNode) {

    SNode* previousNode = nextNode->prev;

    // This while loop iterates backwards until it reaches the first node in the list
    // whose data is less than or equal to the data of the new node that will be inserted
    while ((previousNode != nullptr) && (previousNode->data > newNode->data)) {
        nextNode = previousNode;
        previousNode = nextNode->prev;
    }

    // The new node's pointers are set so that it is linked with the previous node and next node
    newNode->next = nextNode;
    newNode->prev = previousNode;

    // The next node's previous pointer is set to new node
    nextNode->prev = newNode;
    // the previous node's next pointer is set to new node
    previousNode->next = newNode;

}

// The alsoHigher method returns true 50% of the time, it uses
// rand() to generate a random number between 0 and 1 and returns true
// if the number it receives is 0
bool SkipList::alsoHigher() const {

    return (rand() % 2 == 0);
}

// The overloaded output operator for the SkipList will print out the contents of the SkipList to the
// output stream including each depth level, front and rear guards, and the items in each level of
// the Skiplist
ostream& operator<<(ostream& os, const SkipList& list) {

    // Loop through each level in the SkipList, starting at the top level
    for (int i = list.depth - 1; i >= 0; i--) {
        // Sets the current pointer to point to the next node after the frontGuard
        SNode* current = list.frontGuards[i]->next;

        // Print the level of the SkipList and the front guard's data
        os << "Level: " << i << " -- ";
        os << list.frontGuards[i]->data << ", ";

        // Traverses through the nodes on each level and prints each node's data
        while (current != list.rearGuards[i]) {
            os << current->data << ", ";
            current = current->next;
        }

        // Print the data for the rear guard and move to the next line
        os << list.rearGuards[i]->data;
        cout << endl;
    }
    // Returns the output stream object
    return os;
}
