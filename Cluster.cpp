//
//  Cluster.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "Cluster.h"
#include "Point.h"
#include <cstdlib>

namespace Clustering
{
    Cluster::Cluster(const Cluster &c) : size(c.size), head(nullptr)
    {
        
        if (this == &c)
        {
            return;
        }
        else
        {
            LNodePtr *cloud = new LNodePtr;
            head = *cloud;
        }


    }
   
    
    Cluster& Cluster::operator=(const Cluster &c)
    {
        // check for self-assignment
        if (this == &c)
        {
            return *this;
        }
        //if (size != c.size)
        {
            LNodePtr *cloud = new LNodePtr;
            delete [] head;
            head = *cloud;
        }
        return *this;
    }
    
    Cluster::~Cluster()
    {
        LNodePtr currentNodePtr = head; // Initialize nodePtr to head of list
        LNodePtr nextNodePtr = nullptr;
        while (currentNodePtr != nullptr)
        {
            nextNodePtr = currentNodePtr->next;
            delete currentNodePtr;
            currentNodePtr = nextNodePtr;
        }
        delete currentNodePtr;
    }
    
    void Cluster::add(const PointPtr &value)
    {
        
        LNodePtr newNode = new LNode; // create a new node
        LNodePtr previousPtr = nullptr;
        LNodePtr nodePtr;
        
        newNode->p = value;   // sets pointptr p to the ptr address
        
            if (!head)  // if there isn't a head pointer, this creates it
            {
                head = newNode;
                newNode->next = nullptr; // sets listptr to the next node in the list to null
            }
            else
            {
                nodePtr = head; // Initialize nodePtr to head of list
                previousPtr = nullptr; // Initialize previousNode to null
                
                // Skip all nodes whose value is less than point
                while (nodePtr != nullptr && nodePtr->p < value)
                {
                    previousPtr = nodePtr;
                    nodePtr = nodePtr->next;
                }
                
                // If the new node is to be the 1st in the list,
                // insert it before all other nodes.
                if (previousPtr == nullptr)
                {
                    head = newNode;
                    newNode->next = nodePtr;
                }
                else    // otherwise insert after the previous node
                {
                    previousPtr->next = newNode;
                    newNode->next = nodePtr;
                }
            }
    }
    
    const PointPtr& Cluster::remove(const PointPtr &value)
    {
        LNodePtr nodePtr;
        LNodePtr previousPtr = nullptr;
        
        // If list is empty do nothing
        if (!head)
            return value;
        
        // Determine if the first node is the one.
        if (head->p == value)
        {
            nodePtr = head->next;
            delete head;
            head = nodePtr;
            size--;
        }
        else
        {
            // Initialize nodePtr to head of list
            nodePtr = head;
            
            // Skip all nodes whose value member is
            // not equal to num
            while (nodePtr != nullptr && nodePtr->p != value)
            {
                previousPtr = nodePtr;
                nodePtr = nodePtr->next;
            }
            
            // If nodePtr is not at the end of the list,
            // link the previous node to the node after nodePtr,
            // then delete nodePtr
            if (nodePtr)
            {
                previousPtr->next = nodePtr->next;
                delete nodePtr;
                size--;
            }
        }
        return value;
    }
    
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        LNodePtr nodePtrL, nodePtrR = new LNode; // initializing node for traversing lhs, rhs
        
        if (lhs.size != rhs.size) // if not the same size, obviously not equal to each other
        {
            return false;
        }
        else
        {
            nodePtrL = lhs.head;    // set left side startiing point equal to
            nodePtrR = rhs.head;    // right side starting point since of same size
            while (nodePtrL && nodePtrR)
            {
                if (nodePtrL->p != nodePtrR->p) // If the values are not equal, return 0
                    return false;
                if (nodePtrL->next && nodePtrR->next)   // If values can continue on both side set
                                                        // both side to the next node
                {
                    nodePtrL = nodePtrL->next;
                    nodePtrR = nodePtrR->next;
                }
                
            }   // if exiting while loop, at the same time under conditions
                // both clusters must be equal
            return true;
        }
    }
    
    Cluster& Cluster::operator+=(const Cluster &rhs)
    {
        LNodePtr currentNode = rhs.head;
        while (currentNode != nullptr)
        {
            this->add(currentNode->p);  // add point that p is pointing to
            currentNode = currentNode->next;
        }
        return *this;   // dereferencing the object
    
    }
    
    Cluster & Cluster::operator-=(const Cluster &rhs)
    {
        LNodePtr currentNode = rhs.head;
        while (currentNode != nullptr)
        {
            
        }
        return *this;

    }
    
    Cluster & Cluster::operator+=(const Point &rhs)
    {
        return *this;
    }
    
    Cluster & Cluster::operator-=(const Point &rhs)
    {
        return *this;
    }
    
    
    
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster total;
        
        total += lhs;
        total += rhs;
        return total;
        
    }
    
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        
        Cluster total;
        return total;
    }
    
    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        return lhs;
    }
    
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        return lhs;
    }
    
    
    
    
    
    

}
