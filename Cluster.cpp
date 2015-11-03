//
//  Cluster.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "Cluster.h"
#include "Point.h"
#include <stdlib.h>
#include <fstream>
#include <cstdlib>


namespace Clustering
{
    
    unsigned int Cluster::__idGenerator = 1;
    
    Cluster::Cluster(const Cluster &c) : __centroid(c.__dimensionality)
    {
        
        if (this == &c)
        {
            return;
        }
        this -> size = 0;
        
        if (c.size == 0)
        {
            this->__dimensionality = c.__dimensionality;
            this->points = nullptr;
            std::cout << "Creating Empty Cluster\n";
        }
        
        else if (c.points->p != nullptr)
        {
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
    }
    
    
    Cluster& Cluster::operator=(const Cluster &c)
    {
        // check for self-assignment
        if (this == &c)
        {
            return *this;
        }
        if (c.size == 0)
        {
            size = 0;
            return *this;
        }
        if (points->p && this->size != c.size && this->size != 0)
        {
            LNodePtr currentNodePtr = points; // Initialize nodePtr to head of list
            LNodePtr nextNodePtr = nullptr;
            while (currentNodePtr != nullptr && currentNodePtr->p != nullptr)
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
        if (points != nullptr)
        {
            while (currentNodePtr->p != nullptr && currentNodePtr->next != nullptr)
            {
                nextNodePtr = currentNodePtr->next;
                if (!nextNodePtr->p)
                    delete currentNodePtr;
                currentNodePtr = nextNodePtr;
                
            }
            delete currentNodePtr;
        }
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
            while (nodePtr != nullptr && *(nodePtr->p) < *(value))
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
                __centroid_valid = false;
            }
            else    // otherwise insert after the previous node
            {
                previousPtr->next = newNode;
                newNode->next = nodePtr;
                size++;
                __centroid_valid = false;
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
            __centroid_valid = false;
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
                __centroid_valid = false;
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
    
    Cluster & Cluster::operator+=(const Point &rhs)
    {
        
        //Point p(rhs); // make &rhs a pointPtr
        //Cluster newCluster = *this;
        this->add(new Point(rhs));
        //std::cout << "this = " << *this << " endthis\n";
        //std::cout << "this = " << *this << "end this\n";
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
        unsigned dimensions = lhs.__dimensionality;
        Cluster total = Cluster(dimensions);
        
        total += lhs;
        total += rhs;
        return total;
    }
    
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        unsigned dimensions = lhs.__dimensionality;
        Cluster total = Cluster(dimensions);
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        unsigned dimensions = lhs.__dimensionality;
        Cluster total = Cluster(dimensions);
        total += lhs;
        total += *rhs;
        return total;
    }
    
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        unsigned dimensions = lhs.__dimensionality;
        Cluster total = Cluster(dimensions);
        total -= lhs;
        total -= *rhs;
        return total;
    }
    
    std::ostream &operator<<(std::ostream &os, const Cluster &c)
    {
        if (c.points != NULL)
        {
            LNodePtr current = c.points;
            while (current != NULL)
            {
                os << *(current->p) << " : " << c.get_id() << endl;
                current = current->next;
            }
            
        }
        else
        {
            os << "Empty Cluster";
            os << " : " << c.get_id() << endl;
        }
        return os;
        
    }
    
    std::istream &operator>>(std::istream &is, Cluster &c)
    {
        
        string line;
        getline(is, line);
        
        //std::cin.ignore();
        cout << "Line: " << line << endl;
        
        stringstream lineStream(line);
        Point *p = new Point(2);
        
        lineStream >> *p;
        c.add(p);
        
        return is;
    }
    
    void Cluster::pickPoints(int k, PointPtr pointArray[])
    {
        //IF k >= Size
        //IF
        int index = 0;
        
        Cluster::iterator it = points;
        // put first point in pointArray[index]
        pointArray[index] = *it;
        
        __centroid=*(pointArray[index]);
        //cout << "set centroid: " << __centroid << std::endl;
        
        
        
        int step = (size / k);
        
        //std::cout << *pointArray[index] << endl;
        index++;
        while(points->next != nullptr && points->p != nullptr && index < k)
        {
            int counter = step;
            while (counter != 0 && points->next != nullptr && points->p != nullptr)
            {
                it = ++it;
                counter--;
            }
            pointArray[index] = *it;
            __centroid=*(pointArray[index]);
            //cout << "set centroid: " << __centroid << std::endl;
            //std::cout << *(pointArray[index]);
            
            index++;
            
        }
        
    }
    
    Point & Cluster::compute_centroid(Cluster &head)
    {
        Cluster::iterator it = head.points; // Initialize iterator to head of list
        double size = head.size;
        
        if (it != nullptr && it++ != nullptr)
            // if the linked list isn't empty and if the linked list isn't just size 1 (have seperate code to deal with those)
            __centroid = **it / size;
        it = ++it;
        
        while (it != nullptr)
        {
            __centroid += **it / size;
            it = ++it;
        }
        std::cout << "new centroid = " << __centroid;
        __centroid_valid = true;
        return __centroid;
        
    }
    
    void Cluster::makeCentroid()
    {
        __centroid.setDimensionality(__dimensionality);
        
    }
    
    const Point Cluster::get_centroid()
    {
        return __centroid;
    }
    
    
    void Cluster::set_centroid(const Point &p)
    {
        //CENTROID HERE IS NULL?? Do I need dynamic Point? Having problems
        //assigning p to __centroid
        //defined as         Point __centroid = *new Point(__dimensionality);
        //in Cluster private member
        
        cout << __dimensionality;
        //__centroid.setDimensionality(__dimensionality);
        __centroid =  p;
        __centroid_valid = true;
        cout << "set centroid: " << __centroid << std::endl;
    }
    
    
    double Cluster::intraClusterDistance() const
    {
        LNodePtr previousPtr = nullptr;
        LNodePtr currentNodePtr = points;
        
        double sum = 0;
        if (size == 0)
        {
            return 0;
        }
        while(currentNodePtr && currentNodePtr->p)
        {
            previousPtr = currentNodePtr;
            currentNodePtr = currentNodePtr->next;
            while (currentNodePtr != nullptr && previousPtr->p != nullptr)
            {
                if (!(currentNodePtr->p))
                {
                    sum = 0;
                    break;
                }
                
                else
                {
                    sum += (*(currentNodePtr->p)).distanceTo(*(previousPtr->p));
                    currentNodePtr = currentNodePtr->next;
                }
            }
        }
        return ((sum / 2) / this->getClusterEdges());
    }
    
    double interClusterDistance(const Cluster &c1, const Cluster &c2)
    {
        LNodePtr nodePtrL, nodePtrR, previousPtrL, previousPtrR;
        if (c1.size == 0 || c2.size == 0)
        {
            return 0;
        }
        
        nodePtrL = c1.points;
        nodePtrR = c2.points;
        
        double sum;
        
        
        previousPtrL = nodePtrL;
        previousPtrR = nodePtrR;
        
        while (nodePtrL != nullptr && nodePtrR != nullptr)
        {
            if (!(nodePtrL->p && nodePtrR->p))
            {
                sum = 0;
                break;
            }
            previousPtrL = nodePtrL;
            previousPtrR = nodePtrR;
            
            nodePtrL = nodePtrL->next;
            nodePtrR = nodePtrR->next;
            while (nodePtrL != nullptr && nodePtrR != nullptr)
            {
                if (nodePtrL->p != nullptr && nodePtrR->p != nullptr)
                {
                    sum += (*(nodePtrL->p)).distanceTo(*(nodePtrR->p));
                    nodePtrL = nodePtrL->next;
                    nodePtrR = nodePtrR->next;
                }
                
            }
        }
        return (sum / getInterClusterEdges(c1, c2));
    }
    
    
}

