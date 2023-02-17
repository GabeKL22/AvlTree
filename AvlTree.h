/*
Author:             Gabriel Leffew
Major:              Computer Science
Creation Date:      February 5, 2023
Due Date:           February 16, 2023
Course:             CSC402
Professor Name:     Dr. Zhang
Assignment:         #1
Filename:           AvlTree.h
Purpose:            Create an AVL tree and functions to traverse and balance the tree
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <stack>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        cout << "Sorry, remove unimplemented; " << x <<
                " still present" << endl;
    }

    /**
     * Deep copy.
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

    //USER DEFINED
    int count() {
        return count(root);
    }
    void preOrder() {
        return preOrder(root);
    }
    void postOrder() {
        return postOrder(root);
    }
    void kthSmallest(int k) {
        return kthSmallest(root, k);
    }


  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == NULL )
            t = new AvlNode( x, NULL, NULL );
        else if( x < t->element )
        {
            insert( x, t->left );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {
            insert( x, t->right );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else
            ;  // Duplicate; do nothing
        t->height = max( height( t->left ), height( t->right ) ) + 1;

    //ITERATIVELY
        // AvlNode* curr = t;
        // AvlNode* parent = NULL;

        // if (t == NULL) {
        //     t = new AvlNode(x, NULL, NULL);
        //     return;
        // }
        // while (curr != NULL) {
        //     parent = curr;
        //     if (x < curr->element) {
        //         curr = curr->left;
        //     }
        //     else {
        //         curr = curr->right;
        //     }
        // }
        // if (x < parent->element) {
        //     parent->left = new AvlNode(x, NULL, NULL);
        // }
        // else {
        //     parent->right = new AvlNode(x, NULL, NULL);
        // }

    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }


    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != NULL )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /*
    Function name: doubleWithLeftChild
    Description:  
                 * Double rotate binary tree node: first left child.
                 * with its right child; then node k3 with new left child.
                 * For AVL trees, this is a double rotation for case 2.
                 * Update heights, then set new root. 
    Parameters:    Avl * &k3 - node to be flipped
    Return value:  void
    */ 
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        //cout << "LEFTRIGHT -- Working\n";
        // rotateWithRightChild( k3->left );
        // rotateWithLeftChild( k3 );
        //check for leaf nodes (wouldn't work without)
        if (k3 && k3->left && k3->left->right) {
            AvlNode *k1 = k3->left;
            AvlNode *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k3->left = k2->right;
            k2->right = k3;
            // fix the heights
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k3->height = max(height(k3->left), height(k3->right)) + 1;
            k2->height = max(k1->height, k3->height) + 1;
            k3 = k2; //set the new root
        }
    }


    /*
    Function name: doubleWithRightChild
    Description: 
                 * Double rotate binary tree node: first right child.
                 * with its left child; then node k1 with new right child.
                 * For AVL trees, this is a double rotation for case 3.
                 * Update heights, then set new root.
    Parameters:    Avl * &k1 - node to be flipped
    Return value:  void
    */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        //cout << "RIGHTLEFT -- Working\n";
        // rotateWithLeftChild( k1->right );
        // rotateWithRightChild( k1 );
        //check for leaf nodes
        if (k1 && k1->right && k1->right->left) {
            AvlNode *k2 = k1->right;
            AvlNode *k3 = k2->left;
            k2->left = k3->right;
            k3->right = k2;
            k1->right = k3->left;
            k3->left = k1;
            // fix heights
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k3->height = max(k2->height, k1->height) + 1;
            k1 = k3; //set the new root
        }
    }


    ///// PERSONALLY DEFINED FUNCTION
    /*
    Function name: count
    Description:   Count the number of nodes in the AVL tree
    Parameters:    Avl *t - the root of the tree
    Return value:  (left + right + 1) - number of nodes to the left and right of the root
    */
    int count(AvlNode *t) const {
        if (t == NULL) {
            return 0;
        }

        int left = count(t->left);
        int right = count(t->right);

        return left + right + 1;
    }
    /*
    Function name: preOrder
    Description:   Traverse the AVL tree in a preorder
    Parameters:    Avl *t - the root of the tree
    Return value:  void function does not return a value
    */
    void preOrder(AvlNode *t) {
        if (t == NULL) {
            return;
        }
        cout << t->element << " ";
        preOrder(t->left);
        preOrder(t->right);
    }
    /*
    Function name: postOrder
    Description:   Traverse the AVL tree in a postorder
    Parameters:    Avl *t - the root of the tree
    Return value:  void function does not return a value
    */
    void postOrder(AvlNode *t) {
        if (t == NULL) {
            return;
        }
        postOrder(t->left);
        postOrder(t->right);
        cout << t->element << " ";
    }
    /*
    Function name: kthSmallest
    Description:   Keep count of the nodes visited to find the k'th value
                   and outputs the k'th value if found.
    Parameters:    Avl *t - the root of the tree
                   int k  - the k'th value wanting to be searched for
    Return value:  void function does not return a value
    */
    void kthSmallest(AvlNode* t, int k) {
        int cnt = 0;
        AvlNode* result = kth(t, cnt, k);
        if (result == NULL) {
            cout << "the k'th smallest element was not found.";
        }
        else {
            cout << "The " << k << "'th smallest value in the AVL tree is " << result->element << ".";
        }

    }
    /*
    Function name: kth
    Description:   recursive function to find k'th value in the
                   AVL tree, when count = k it has been found.
    Parameters:    Avl *t - the root of the tree
                   int &cnt - keep count of the k'th value you're on
                   int k - the k'th value you're searching for
    Return value:  NULL - if empty
                   t - the root node you're at if found
    */
    AvlNode* kth(AvlNode* t, int &cnt, int k) {
        if (t == NULL) {
            return NULL;
        }
        AvlNode* left = kth(t->left, cnt, k);
        if (left != NULL) {
            return left;
        }
        cnt++;
        if (cnt == k) {
            return t;
        }
        return kth(t->right, cnt, k);
    }

};

#endif
