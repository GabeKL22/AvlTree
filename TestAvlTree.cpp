/*
Author:             Gabriel Leffew
Major:              Computer Science
Creation Date:      February 5, 2023
Due Date:           February 16, 2023
Course:             CSC402
Professor Name:     Dr. Zhang
Assignment:         #1
Filename:           TestAvlTree.cpp
Purpose:            File to test the AVL tree and it's functions from AvlTree.h
*/
#include <iostream>
#include "AvlTree.h"
#include <vector>
#include<bits/stdc++.h>

using namespace std;

// Test program
/*
Function name: main
Description:   Test the AVL tree and all it's functions from AvlTree.h
Parameters:    none
Return value:  0
*/
int main( )
{
    AvlTree<int> t;
    int i, a, k;
    int searchValue;
    //vector to store vales of any size
    vector <int> treeNodes;

    //Enter tree nodes
    cout << "Enter a sequence of integers to build the AVL tree (enter -1 to end): ";
    while ((cin >> a) && a != -1) {
        treeNodes.push_back(a);
    }
    //insert nodes into tree
    for( i = 0; i != treeNodes.size(); i++) {
        t.insert(treeNodes[i]);
    }
    //Count nodes in tree
    cout << "\nThe AVL tree has " << t.count() << " nodes in total." << endl;
    //t.printTree( );

    //preorder traversal
    cout << "\nPre-Order tree traversal: ";
    t.preOrder();
    //postorder traversal
    cout << "\n\nPost-order tree traversal: ";
    t.postOrder();
    //search for value
    cout << "\n\nSearch for value: ";
    cin >> searchValue;
    cout << "\n";
    if (t.contains(searchValue)) {
        cout << searchValue << " is in the AVL tree\n";
    }
    else {
        cout << searchValue << " is NOT in the AVL tree\n";
    }
    //search for k'th smallest value
    cout << "\nSearch for the k'th smallest value. Enter k: ";
    cin >> k;
    cout << "\n";
    
    t.kthSmallest(k);

    cout << "\nTest finished" << endl;
    return 0;
}
