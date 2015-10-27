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
        //friend class Centroid;
    private:
        
        
        unsigned int __id;
        unsigned int __dimensionality;
        // A static id generator method. It should be invoked by all constructors.
        static unsigned int __idGenerator;
        bool __centroid_valid;
        
        // Validate and invalidate a centroid and check for validity. Hint: Use a private boolean flag and corresponding methods. Any function or operator which changes the point composition of the cluster should invalidate its centroid.
        
        
        Point __centroid;
        
        
        
        
    public:
        const LNodePtr get_points() {return points;};
        
        unsigned int get_id() const {return __id;};
        // Set the centroid. Should take a const Point &.
        // Only the centroid setter and computer should set it back to valid.
        void set_centroid(const Point &);
        
        const Point get_centroid();
        
        Point & compute_centroid(Cluster &);
        
        bool get_centroid_valid() {return __centroid_valid;};
        
        //to be able to specify whether the class should deallocate points that are pointed to by its nodes
        bool release_Points;
        
        
        // Need to add and unsigned int
        // Cluster (unsigned d) : __centroid (_dimensionality), _dimensionality(d);
        Cluster(unsigned d) :
        __dimensionality(d),
        __centroid (__dimensionality),
        __id(__idGenerator++)
        {};
        
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
        
        double &operator[](int index);  // overload to access point
        
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
        
        //  to pick k points from a cluster that would serve as the initial set of centroids. The function takes in a Point array that it needs to populate. You are free to implement the selection strategy as you wish. Hint: Generally, the more distant the points from each other, the better for the outcome of the KMeans algorithm. You might use the fact that points in a Cluster are sorted lexicographically. At the very least, don't pick the first k :)
        void pickPoints(int k, PointPtr *pointArray);
        
        // A public getter for the size. It will be helpful with testing and debugging your KMeans implementation.
        const int getSize() {return size;};
        
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
        
        // Methods for scoring the clustering (used in the requirements for KMeans):
        // Same thing as (1), but between two clusters.
        double intraClusterDistance() const;
        
        // This is the sum of the distances between every two points in the cluster. Hint: This can be done in a double loop through the points of the cluster. However, this will count every distance twice, so you need to divide the sum by 2 before returning it.
        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);
        
        
        // This returns the number of distinct edges in a cluster. (That is, every two distinct points have an imaginary edge between them. It's length is the distance between the two points.) This is simply size * (size - 1) / 2, where size is the size of the cluster.
        int getClusterEdges() const {return (size * (size - 1) / 2);};
        
        friend int getInterClusterEdges(const Cluster &c1, const Cluster &c2)
        {return (c1.size + c2.size) * (c1.size + c2.size - 1) / 2;};
        
        
    };
}


#endif //CLUSTERING_CLUSTER_H