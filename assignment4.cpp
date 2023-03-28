//Name: David Schurer
//Class: CSS 342
//Assignment 4: Skiplist
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <random>
#include "skiplist.h"
using namespace std;

// The test function singleLevelSkipListTest will test the Add, Remove, and Contains methods
// on a SkipList that has just a single level
void singleLevelSkipListTest() {

    SkipList singleLevelSkipList(1);

    singleLevelSkipList.Add(84);
    cout << "After adding 84" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Add(66);
    cout << "After adding 66" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Add(21);
    cout << "After adding 21" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Add(-5);
    cout << "After adding -5" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Add(-20);
    cout << "After adding -20" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Remove(66);
    cout << "After removing 66" << endl;
    cout << singleLevelSkipList << endl;

    singleLevelSkipList.Remove(-5);
    cout << "After removing -5" << endl;
    cout << singleLevelSkipList << endl;

    assert(singleLevelSkipList.Contains(84) == true);
    cout << "The skiplist contains 84" << endl;

    assert(singleLevelSkipList.Contains(21) == true);
    cout << "The skiplist contains 21" << endl;

    assert(singleLevelSkipList.Add(84) == false);
    cout << "Cannot add a duplicate of 84 into the skiplist" << endl;

    assert(singleLevelSkipList.Add(21) == false);
    cout << "Cannot add a duplicate of 21 into the skiplist" << endl;

}

// The test function twoLevelSkipListTest will test the Add, Remove, and Contains methods
// on a SkipList that has 2 levels
void twoLevelSkipListTest() {

    SkipList smallSkipList(2);

    smallSkipList.Add(898);
    cout << "After adding 898" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Add(-24);
    cout << "After adding -24" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Add(57);
    cout << "After adding 57" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Add(1024);
    cout << "After adding 1024" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Add(404);
    cout << "After adding 404" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Add(-111);
    cout << "After adding -111" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Remove(1024);
    cout << "After removing 1024" << endl;
    cout << smallSkipList << endl;

    smallSkipList.Remove(57);
    cout << "After removing 57" << endl;
    cout << smallSkipList << endl;

    assert(smallSkipList.Contains(404) == true);
    cout << "The skiplist contains 404" << endl;

    assert(smallSkipList.Contains(-111) == true);
    cout << "The skiplist contains -111" << endl;

    assert(smallSkipList.Add(404) == false);
    cout << "Cannot add a duplicate of 404 into the skiplist" << endl;

    assert(smallSkipList.Add(-111) == false);
    cout << "Cannot add a duplicate of -111 into the skiplist" << endl;

}

// The test function fiveLevelSkipListTest will test the Add, Remove, and Contains methods
// on a SkipList that has 5 levels
void fiveLevelSkipListTest() {

    SkipList mediumSkipList(5);

    mediumSkipList.Add(-10);
    cout << "After adding -10" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(-5);
    cout << "After adding -5" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(5);
    cout << "After adding 5" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(10);
    cout << "After adding 10" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(15);
    cout << "After adding 15" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(20);
    cout << "After adding 20" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(25);
    cout << "After adding 25" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(30);
    cout << "After adding 30" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(35);
    cout << "After adding 35" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Add(40);
    cout << "After adding 40" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Remove(-10);
    cout << "After removing -10" << endl;
    cout << mediumSkipList << endl;

    mediumSkipList.Remove(30);
    cout << "After removing 30" << endl;
    cout << mediumSkipList << endl;

    assert(mediumSkipList.Contains(20) == true);
    cout << "The skiplist contains 20" << endl;

    assert(mediumSkipList.Contains(40) == true);
    cout << "The skiplist contains 40" << endl;

    assert(mediumSkipList.Add(20) == false);
    cout << "Cannot add a duplicate of 20 into the skiplist" << endl;

    assert(mediumSkipList.Add(40) == false);
    cout << "Cannot add a duplicate of 40 into the skiplist" << endl;

}

// The test function tenLevelSkipListTest will test the Add, Remove, and Contains methods
// on a SkipList that has 10 levels
void tenLevelSkipListTest() {

    SkipList largeSkipList(10);

    largeSkipList.Add(42);
    cout << "After adding 42" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(6823);
    cout << "After adding 6823" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(4122);
    cout << "After adding 4122" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(601);
    cout << "After adding 601" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(394);
    cout << "After adding 394" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(9999);
    cout << "After adding 9999" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add (-295);
    cout << "After adding -295" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(-5293);
    cout << "After adding -5293" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(71);
    cout << "After adding 71" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(122);
    cout << "After adding 122" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(42);
    cout << "After adding 42" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(318);
    cout << "After adding 318" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(696);
    cout << "After adding 696" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(888);
    cout << "After adding 888" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Add(1000);
    cout << "After adding 1000" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Remove(394);
    cout << "After removing 394" << endl;
    cout << largeSkipList << endl;

    largeSkipList.Remove(4122);
    cout << "After removing 4122" << endl;
    cout << largeSkipList << endl;

    assert(largeSkipList.Contains(1000) == true);
    cout << "The skiplist contains 1000" << endl;

    assert(largeSkipList.Contains(-5293) == true);
    cout << "The skiplist contains -5293" << endl;

    assert(largeSkipList.Add(1000) == false);
    cout << "Cannot add a duplicate of 1000 into the skiplist" << endl;

    assert(largeSkipList.Add(-5293) == false);
    cout << "Cannot add a duplicate of -5293 into the skiplist" << endl;

}

int main() {

    cout << "############### TEST 1: SINGLE LEVEL SKIPLIST ###############" << endl;
    singleLevelSkipListTest();
    cout << "#############################################################" << endl;

    cout << endl;

    cout << "############### TEST 2: TWO LEVEL SKIPLIST ###############" << endl;
    twoLevelSkipListTest();
    cout << "##########################################################" << endl;

    cout << endl;

    cout << "############### TEST 3: FIVE LEVEL SKIPLIST ###############" << endl;
    fiveLevelSkipListTest();
    cout << "###########################################################" << endl;

    cout << endl;

    cout << "############### TEST 4: TEN LEVEL SKIPLIST ###############" << endl;
    tenLevelSkipListTest();
    cout << "##########################################################" << endl;

    cout << endl;

    return 0;
}
