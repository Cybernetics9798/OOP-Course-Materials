#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root = nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL
    deleteTree();
    //delete root;
    root = nullptr;
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
}

// Public Interface, Implemented
void objPosBST::printTree() const
{    
    printTree(root);  // recursive call on the private helper function
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

// Public Interface, Implemented
bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root); // recursive call on the private helper function
}

// Public Interface, Implemented
bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root); // recursive call on the private helper function
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    if(root == nullptr)
    {
        return true;
    }
    return false;
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    // Definately Post-Order!
    //   WARNING - using the wrong one will result in potential heap error.
    TNode* temp;
    if(thisNode != nullptr)
    {
        temp = thisNode->left;
        delete thisNode;
        deleteTree(temp);
        temp = thisNode->right;
        deleteTree(temp);
    }
}

void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**
    // use printObjPos() method in objPos class for formatted print
    if(thisNode == nullptr)
    {
        return;
    }
    printTree(thisNode->left);
    thisNode->data.printObjPos();
    printTree(thisNode->right);
    thisNode->data.printObjPos();
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true

    if(thisNode == nullptr){
        return false;
    }

    if(thisPos.getPF() < thisNode->data.getPF()){
        return isInTree(thisPos, thisNode->left);
    }else if(thisPos.getPF() > thisNode->data.getPF()){
        return isInTree(thisPos, thisNode->right);
    }else if(thisPos.getPF() == thisNode->data.getPF()){
        return true;
    }
    return false;
}



// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)

    if(thisNode == nullptr){
        thisNode = new TNode(thisPos);
    }else if(thisPos.getPF() < thisNode->data.getPF()){
        insert(thisPos, thisNode->left);
    }else if(thisPos.getPF() > thisNode->data.getPF()){
        insert(thisPos, thisNode->right);
    }else if(thisPos.getPF() == thisNode->data.getPF()){
        thisNode->data.setNum(thisNode->data.getNum() + thisPos.getNum());
    }
}

const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode
    // Used as part of remove() algorithm
    // Check Lecture Notes for implementation
    if(thisNode->left == nullptr)
    {
        return thisNode;
    }
    return findMin(thisNode->left);
}

void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
    if(thisNode == nullptr){
        return;
    }
    
    if(thisPos.getPF() < thisNode->data.getPF()){
        remove(thisPos, thisNode->left);
    }else if(thisPos.getPF() > thisNode->data.getPF()){
        remove(thisPos, thisNode->right);
    }else if(thisPos.getPF() == thisNode->data.getPF()){
        if(thisNode->left != nullptr && thisNode->right != nullptr){
            thisNode->data = findMin(thisNode->right)->data;
            remove(thisNode->data, thisNode->right);
        }else{
            TNode* oldNode = thisNode;
            if(thisNode->left == nullptr){
                thisNode = thisNode->right;
            }else if(thisNode->right == nullptr){
                thisNode = thisNode->left;
            }
            delete oldNode;
        }
    }
}

bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes
    if(thisNode == nullptr){
        return false;
    }

    if(thisNode->data.getPF() == thisPos.getPF()){
        if(thisNode->left == nullptr && thisNode->right == nullptr){
            return true;
        }
    }else{
        if(thisPos.getPF() < thisNode->data.getPF()){
            return isLeaf(thisPos, thisNode->left);
        }else if(thisPos.getPF() > thisNode->data.getPF()){
            return isLeaf(thisPos, thisNode->right);
        }
    }
    return false;
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
    if(thisNode == nullptr){
        return false;
    }
    bool checkLeft = findGreater(numThreshold, thisNode->left);
    if(checkLeft == true){
        return true;
    }
    bool checkRight = findGreater(numThreshold, thisNode->right);
    if(checkRight == true){
        return true;
    }
    bool checkCurrent = thisNode->data.getNum() > numThreshold;
    if(checkCurrent == true){
        return true;
    }
    return false;
}