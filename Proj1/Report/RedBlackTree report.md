### Implement

Red Black Tree

#### Insert

1. Let  x be the root of the tree. Assign `Nil` to the left and right Child of newNode. Assign RED color to newNode.
2. Check if the tree is empty (ie. whether x is `NIL`). If yes, insert new Node as a root node and color it black.
3. Else, find the leaf node as search in a binary search tree.
4. Assign the parent of the leaf as a parent of newNode.
5. If leaf Key  >  newKey, make newNode as right Child. Else, make newNode as left Child.
6. Call InsertFix-algorithm to maintain the property of red-black tree if violated.

#### InsertFix

This algorithm is used for maintaining the property of a red-black tree if the insertion of a newNode violates this property.

1. Do the following while the parent of newNode p is RED.

2. If p is the left child of grandparent z, do the following.

   Case-I:

   If right child of gp is RED, set the color of both the children of gP as BLACK and the color of gP as RED.

   Assign gP to newNode.
   **Case-II:**

   Else if newNode is the right child of p then, assign p to newNode.  Left-Rotate newNode.
   **Case-III:**

   Set color of p as BLACK and color of gP as RED.

   Right-Rotate gP.

3. If p is the left child of grandparent z, do the following.

   - If the sibling is RED, set the color of both the children of gP as BLACK and the color of gP as RED.

   - Assign gP to newNode.

   - Else if newNode is the left child of p then, assign p to newNode and Right-Rotate newNode.

   - Set color of p as BLACK and color of gP as RED.

   - Left-Rotate gP.

4. Set the root of the tree as BLACK.

#### delete a node

z is the node to be deleted.

1. Save the color of nodeToBeDeleted in origrinalColor.

2. If the left child of z is nil:

   Assign the right child of nodeToBeDeleted to x.

   Transplant nodeToBeDeleted with x.

3. Else if the right child of z is nil:

   Assign the left child of nodeToBeDeleted into x.

   Transplant nodeToBeDeleted with x.

4. Else

   1. Assign the minimum of right subtree of noteToBeDeleted into y.
   2. Save the color of y in originalColor.
   3. Assign the rightChild of y into x.
   4. If y is a child of nodeToBeDeleted, then set the parent of x as y.
   5. Else, transplant y with rightChild of y.
   6. Transplant nodeToBeDeleted with y.
   7. Set the color of y with originalColor.

5. If the originalColor is BLACK, invoke DeleteFix(x).

#### deletefix

This violation is corrected by assuming that node x (which is occupying y's original position) has an extra black. This makes node x neither red nor black. It is either doubly black or black-and-red. This violates the red-black properties.

However, the color attribute of x is not changed rather the extra black is represented in x's pointing to the node.

The extra black can be removed if 

1. It reaches the root node.
2. If x points to a red-black node. In this case, x is colored black.
3. Suitable rotations and recolouring are performed.

The following algorithm retains the properties of a red-black tree.

1. Do the following until the x is not the root of the tree and the color of x is BLACK

2. If x  is the left child of its parent then,

   1. if the sibling of x  is red, 

      Case-I:

      1. Set the color of the right child of the parent of x as BLACK.
      2. Set the color of the parent of x as RED.
      3. Left-Rotate the parent of x.

   2. If the sibling has two BLACK children.

      Case-II:

      1. Set sibling  as RED
      2. upward 

   3. Else if the color of s is BLACK

      Case-III:

      1. Set the color of the leftChild of s as BLACK
      2. Set the color of s as RED
      3. Right-Rotate s.
      4. reassign s as sibling.

   4. If any of the above cases do not occur, then do the following.

      Case-IV:

      1. Set the color of s as the color of the parent of x.
      2. Set the color of the parent of x as BLACK.
      3. Set the color of the right child of s as BLACK.
      4. Left-Rotate the parent of x.
      5. Set x as the root of the tree.

3. Else the same as above with right changed to left and vice versa.

4. Set the color of x as BLACK.



### Problem

1 [How to automatically generate function headers for .h file in Clion?](https://stackoverflow.com/questions/34288513/how-to-automatically-generate-function-headers-for-h-file-in-clion)

``` c
void RedBlackTree::initializeNULLNode(NodePtr node, NodePtr parent) { xxx
```

We cannot redefine function in .cpp, we just implement function like codes above in .cpp.

2 MSVCRTD.lib(exe_main.obj) : error LNK2019

because we don't have main function.

3. this file does not belong to any project target

clion alt +enter cannot split

