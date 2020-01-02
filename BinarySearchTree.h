// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Katherine Lee

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType&, ItemType&));
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    bool _search(BinaryNode<ItemType>* treePtr, ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&) );
    
public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry, int compare(ItemType&, ItemType&));
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
    bool search(ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&) );
    
};


///////////////////////// public function definitions ///////////////////////////

// insert a node at the correct location
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry, int compare(ItemType&, ItemType&) )
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

//search nodes
template <class ItemType>
bool BinarySearchTree<ItemType>::search(ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&) )
{
    return _search(this->rootPtr, target, compare, visit );
}



//////////////////////////// private functions ////////////////////////////////////////////

//function COMPARE : 0 = equal, 1 = left > right, -1 = left < right
//the insert function will insert item into the node of the tree
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, int compare(ItemType&, ItemType&))
{
    //function COMPARE : 0 = equal, 1 = left > right, -1 = left < right
    if( nodePtr == nullptr)
    {
        nodePtr = newNodePtr;
        // return nodePtr;
    }
    else
    {
        ItemType rootItem = nodePtr->getItem();
        ItemType newItem = newNodePtr->getItem();
        
        if( compare(newItem, rootItem ) == -1 )     // if new node is smaller than root
        {
            nodePtr->setLeftPtr(_insert (nodePtr->getLeftPtr(), newNodePtr, compare));
        }
        else
        {
            nodePtr->setRightPtr(_insert (nodePtr->getRightPtr(), newNodePtr, compare ));
        }
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}


//the function will find and return the address of target node
template<class ItemType>
bool _search(BinaryNode<ItemType>* nodePtr, ItemType& target, int compare(ItemType&, ItemType&), void visit(ItemType&) )
{
    bool found = false;
    
    if(nodePtr == nullptr)
        return found;
    
    if( compare(nodePtr->getItem(), target) == 1 )
        _search(nodePtr->getLeftPtr(), target, compare, visit);
    else
    {
        if( compare(nodePtr->getItem(), target) == 0  ) {
            found = true;
            visit(nodePtr->getItem());
            
            if ( compare(nodePtr->getItem(), nodePtr->getRightPtr()->getItem() ) == 0 )
                found = _search(nodePtr->getRightPtr(), target, compare, visit);
        }
        else
            found = _search(nodePtr->getRightPtr(), target, compare, visit);
    }
    
    return found;
    
}



#endif
