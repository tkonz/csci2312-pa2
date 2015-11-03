//
//  Cluster.h
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"
#include <cstdlib>


namespace Clustering {
    
    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;
    
    struct LNode { // linked-list node
        PointPtr p;
        LNodePtr next;
    };
    
    class Cluster
    {
        
        int size;
        LNodePtr points; // linked-list head
        
    private:
        unsigned int __id;
        unsigned int __dimensionality;
        static unsigned int __idGenerator;
        bool __centroid_valid;
        Point __centroid;
        
        
    public:
        const Cluster get_Size() {return size;};
        const LNodePtr get_points() {return points;};
        
        unsigned int get_id() const {return __id;};
        
        void makeCentroid();
        
        void set_centroid(const Point &);
        
        const Point get_centroid();
        
        Point & compute_centroid(Cluster &);
        
        bool get_centroid_valid() {return __centroid_valid;};
        
        bool release_Points;
        
        double &operator[](int index); // TODO out-of-bds?
        // Need to add and unsigned int
        // Cluster (unsigned d) : __centroid (_dimensionality), _dimensionality(d);
        Cluster() :
        __dimensionality(0),
        __centroid(0),
        __id(0),
        points(nullptr)
        {size = 0;};
        Cluster(unsigned d) :
        __dimensionality(d),
        __centroid (__dimensionality),
        __id(__idGenerator++),
        points(nullptr)
        
        {size = 0;};
        
        void setDimensionality(int dim) {__dimensionality = dim;};
        
        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();
        
        // Set functions: They allow calling c1.add(c2.remove(p));
        
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);
        
    public:
        class iterator
        {
        private:
            LNodePtr m_CurrentNode;
        public:
            friend class DoublyLinkedList;
            iterator(LNodePtr node = NULL) : m_CurrentNode(node) {}
            
            PointPtr& operator*() const {return m_CurrentNode->p;}
            
            iterator& operator++()
            {
                m_CurrentNode = m_CurrentNode->next;
                return *this;
            }
            
            iterator operator++(int)
            {
                iterator temp = *this;
                m_CurrentNode = m_CurrentNode->next;
                return temp;
            }
            
            bool operator== (const iterator other) const
            {
                return (m_CurrentNode == other.m_CurrentNode);
            }
            
            bool operator !=(const iterator other) const
            {
                return (m_CurrentNode != other.m_CurrentNode);
            }
            
        };
        
        
        // Overloaded operators
        // Set-preserving operators (do not duplicate points in the space)
        // Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);
        
        // Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference
        
        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point
        
        // returns an iterator to the first element in the list
        iterator begin() {return iterator(points);};
        
        // Set-destructive operators (duplicate points in the space)
        // Friends
        
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
        
        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);
        
        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);
        
        void pickPoints(int k, PointPtr pointArray[]);
        
        // A public getter for the size. It will be helpful with testing and debugging your KMeans implementation.
        const int getSize() {return size;};
        
        // returns an iterator to the first element in the list
        
        
        class Move
        {
        private:
            Cluster *m_To;
            Cluster *m_From;
            PointPtr m_Point;
            
            //Constructor taking const PointPtr &ptr, const Cluster &from, Cluster &to
        public:
            Move(const PointPtr &ptr, Cluster *from, Cluster *to)
            {
                m_To = to;
                m_From = from;
                m_Point = ptr;
            };
            
            //Method perform() which invokes c1.add(c2.remove(ptr))
            void perform()
            {
                m_To->add(m_From->remove(m_Point));
                m_From->__centroid_valid = false;
                m_To->__centroid_valid = false;
            };
            
        };
        
        double intraClusterDistance() const;
        
        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);
        
        int getClusterEdges() const {return (size * (size - 1) / 2);};
        
        friend int getInterClusterEdges(const Cluster &c1, const Cluster &c2)
        {return (c1.size + c2.size) * (c1.size + c2.size - 1) / 2;};
        
        
    };
}


#endif //CLUSTERING_CLUSTER_H