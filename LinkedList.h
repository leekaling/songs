#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ListNode.h"

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;      // List head pointer
    int count;           // To keep track of the number of nodes in the list


public:
    LinkedList();  // Constructor
    ~LinkedList() {this->clearList();}   // Destructor

    // Linked list operations
    int getCount() const {return count;}
    ListNode<T>* getHead() {return head;}
    bool insertNode(T);
    bool deleteNode(T);
    void displayList() ;
    bool searchList(T) ;
    void clearList();
};

#endif
