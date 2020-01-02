//
//  ListNode.h
//  22C_H2
//
//  Created by Katherine Lee on 10/13/18.
//  Copyright © 2018 Katherine Lee. All rights reserved.
//

#ifndef ListNode_h
#define ListNode_h

#include "HashNode.h"

// Declare a class for ListNode
template <class T>
struct ListNode
{
    T item;     // The value in this node
    ListNode<T>
    *next;  // To point to the next node

    
};


#endif /* ListNode_h */
