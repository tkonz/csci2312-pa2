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
    
    class Cluster {
        int size;
        LNodePtr head; // linked-list head
        
        
    public:
        Cluster() : size(0), head(nullptr) {};
        
        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();
        
        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);
        
        // Overloaded operators
        
        // Set-preserving operators (do not duplicate points in the space)
        // Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);
        
        // Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference
        
        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point
        
        // Set-destructive operators (duplicate points in the space)
        // Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
        
        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);
        
        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);
        
    };
}
#endif //CLUSTERING_CLUSTER_H