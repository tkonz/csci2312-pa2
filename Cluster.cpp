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
    Cluster::Cluster(const Cluster &c) : size(c.size), points(c.points)
    {
        if (this == &c)
        {
            return;
        }
        this -> size = 0;
        
        LNodePtr headNode = new LNode;
        headNode->p = c.points->p;
        this->points = headNode;
        LNodePtr previousPtr = headNode;
        LNodePtr cursor = c.points->next;
        
        while (cursor != nullptr)
        {
            LNodePtr newNode = new LNode;
            newNode->p = cursor->p;
            previousPtr->next = newNode;
            previousPtr = newNode;
            cursor = cursor->next;
        }
        this->size = c.size;
    }
    
    
    Cluster& Cluster::operator=(const Cluster &c)
    {
        // check for self-assignment
        if (this == &c)
        {
            return *this;
        }
        if (this->size != c.size && this->size != 0)
        {
            LNodePtr currentNodePtr = points; // Initialize nodePtr to head of list
            LNodePtr nextNodePtr = nullptr;
            while (currentNodePtr->p != nullptr && currentNodePtr->next != nullptr)
            {
                nextNodePtr = currentNodePtr->next;
                if (!nextNodePtr->p)
                    delete currentNodePtr;
                currentNodePtr = nextNodePtr;
            }
            delete currentNodePtr;
        }
        this -> size = 0;
        
        LNodePtr headNode = new LNode;
        headNode->p = c.points->p;
        this->points = headNode;
        LNodePtr previousPtr = headNode;
        LNodePtr cursor = c.points->next;
        
        while (cursor != nullptr)
        {
            LNodePtr newNode = new LNode;
            newNode->p = cursor->p;
            previousPtr->next = newNode;
            previousPtr = newNode;
            cursor = cursor->next;
        }
        this->size = c.size;
        return *this;
        
    }
    
    Cluster::~Cluster()
    {
        LNodePtr currentNodePtr = points; // Initialize nodePtr to head of list
        LNodePtr nextNodePtr = nullptr;
        
        while (currentNodePtr->p != nullptr && currentNodePtr->next != nullptr)
        {
            nextNodePtr = currentNodePtr->next;
            if (!nextNodePtr->p)
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
        
        if (!points)  // if there isn't a head pointer, this creates it
        {
            points = newNode;
            size++;
            newNode->next = nullptr; // sets listptr to the next node in the list to null
        }
        else
        {
            nodePtr = points; // Initialize nodePtr to head of list
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
                points = newNode;
                newNode->next = nodePtr;
                size++;
            }
            else    // otherwise insert after the previous node
            {
                previousPtr->next = newNode;
                newNode->next = nodePtr;
                size++;
            }
        }
    }
    
    const PointPtr& Cluster::remove(const PointPtr &value)
    {
        LNodePtr nodePtr;
        LNodePtr previousPtr = nullptr;
        
        // If list is empty do nothing
        if (!points)
            return value;
        
        // Determine if the first node is the one.
        if (*(points->p) == *(value))
        {
            nodePtr = points->next;
            delete points;
            points = nodePtr;
            size--;
        }
        else
        {
            // Initialize nodePtr to head of list
            nodePtr = points;
            
            // Skip all nodes whose value member is
            // not equal to num
            while (nodePtr != nullptr && (*(nodePtr->p) != *(value)))
            {
                //std::cout << "enetered while loop\n";
                previousPtr = nodePtr;
                nodePtr = nodePtr->next;
                
            }
            // If nodePtr is not at the end of list, link the previous node
            // to the node after nodePtr, then delete nodePtr
            if (nodePtr)
            {
                //std::cout << "entered if statement.\n";
                previousPtr->next = nodePtr->next;
                delete nodePtr;
                size--;
            }
            
        }
        return points->p;
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
            nodePtrL = lhs.points;    // set left side startiing point equal to
            nodePtrR = rhs.points;    // right side starting point since of same size
            while (nodePtrL && nodePtrR && nodePtrL->next && nodePtrR->next)
            {
                if (*(nodePtrL->p) != *(nodePtrR->p)) // If the values are not equal, return 0
                    return false;
                if (nodePtrL->next && nodePtrR->next)      // If values can continue on both side set
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
        LNodePtr currentNode = rhs.points;
        while (currentNode != nullptr)
        {
            this->add(currentNode->p);  // add point that p is pointing to
            currentNode = currentNode->next;
        }
        return *this;   // dereferencing the object
        
    }
    
    Cluster & Cluster::operator-=(const Cluster &rhs)
    {
        LNodePtr currentNode = rhs.points;
        while (currentNode != nullptr)
        {
            LNodePtr nodePtrL = this->points;
            LNodePtr nodePtrR = rhs.points;
            while (nodePtrR != nullptr)
            {
                if (nodePtrR->p == nodePtrL->p)
                {
                    this->remove(currentNode->p);    // remove point from Cluster
                    currentNode = currentNode->next;
                }
            }
            
        }
        return *this;
        
    }
    //Cluster & Cluster::operator+=(const PointPtr *rhs) {
    
    //}
    
    Cluster & Cluster::operator+=(const Point &rhs)
    {
        
        Point p(rhs); // make &rhs a pointPtr
        this->add(&p);
        
        return *this;
    }
    
    Cluster & Cluster::operator-=(const Point &rhs)
    {
        Point p = rhs;
        this->remove(&p);
        //std::cout << "*this = " << *this << std::endl;
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
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster total;
        total += lhs;
        total += *rhs;
        return total;
    }
    
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster total;
        total -= lhs;
        total -= *rhs;
        return total;
    }
    
    std::ostream &operator<<(std::ostream &os, const Cluster &c)
    {
        LNodePtr current = c.points;
        while (current != NULL)
        {
            os << *(current->p);
            current = current->next;
        }
        return os;
    }
    
    std::istream &operator>>(std::istream &is, Cluster &c)
    {
        
        LNodePtr current = c.points;
        while (current != NULL)
        {
            is >> *(current->p);
            current = current->next;
        }
        return is;
    }
    
    
}
