# AvlTree

### This is the implementation of a self balancing binary search tree.
To start the program clone the repository and run:

`g++ TestAvlTree.cpp -o TestAvlTree`

This will make an executable file named `TestAvlTree` that you can run by typing:

`./TestAvlTree`

From there you can enter your numbers into the Avl Tree, they will be stored in a vector than inserted into the tree using the insert() function, this automatically does the roatations. 

### Other Features

- `preOrder()` Traverses the tree using Pre-Order
- `postOrder()` Traverses the tree using Post-Order
- `count()` Counts the number of nodes in the tree
- `contains()` Prompts the user for an input (number) and returns True or False if it is in the Avl Tree
- `kth()` Find the k'th smallest value in the Avl Tree (Ex. insert(1, 3, 4, 9) - kth(2) == 3) 
