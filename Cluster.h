//
//  Cluster.h
//  pa4_ucd2312
//
//  Created by Tisha Konz on 10/29/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#ifndef __pa4_ucd2312__Cluster__
#define __pa4_ucd2312__Cluster__

#include <stdio.h>
#include "Point.h"
#include <forward_list>
#include <cstdlib>

namespace Clustering {
    
    
    template <typename T>
    class Cluster
    {
        friend class Move;
        
    private:
        int m_Size;
        unsigned int m_Id;
        unsigned int m_Dimensionality;
        static unsigned int m_IdGenerator;
        bool m_Centroid_Valid;
        Point<T> m_Centroid;
        
    public:
        const Cluster get_Size() {return m_Size;};
        unsigned int get_id() const {return m_Id;};
        std::forward_list<Point<T>> m_Points;
        
        
        void makeCentroid();
        void set_centroid(Point<T> &);
        const Point<T> get_centroid();
        Point<T>& compute_centroid(Cluster &);
        bool get_centroid_valid() {return m_Centroid_Valid;};
        
        Cluster<T>(unsigned d) :
        m_Dimensionality(d),
        m_Centroid (m_Dimensionality),
        m_Id(m_IdGenerator++)
        //m_Points()
        
        {m_Size = 0;};
        
        void setDimensionality(int dim) {m_Dimensionality = dim;};
        
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        
        void add(const Point<T> &);
        void remove(const Point<T> &);
        
        template <typename U>
        friend bool operator==(const Cluster<U> &lhs, const Cluster<U> &rhs);
        
        
        // Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference
        
        Cluster &operator+=(const Point<T> &rhs); // add point
        Cluster &operator-=(const Point<T> &rhs); // remove point
        
        Point<T> &operator[](int index); // TODO out-of-bds?
        
        // Set-destructive operators (duplicate points in the space)
        // Friends
        
        template <typename U>
        friend const Cluster<U> operator+(const Cluster<U> &lhs, const Cluster<U> &rhs);
        template <typename U>
        friend const Cluster<U> operator-(const Cluster<U> &lhs, const Cluster<U> &rhs);
        
        template <typename U>
        friend const Cluster<U> operator+(const Cluster<U> &lhs, const Point<U> &rhs);
        template <typename U>
        friend const Cluster<U> operator-(const Cluster<U> &lhs, const Point<U> &rhs);
        
        // IO
        template <typename U>
        friend std::ostream &operator<<(std::ostream &, const Cluster<U> &);
        template <typename U>
        friend std::istream &operator>>(std::istream &, Cluster<U> &);
        template <typename U>
        friend std::istream &operator>>(std::istream &, Cluster<U> &);
        
        void pickPoints(int k, std::vector<Point<T>> &pointVec);
        
        int get_size() {return m_Size;};
        
        double intraClusterDistance() const;
        
        template <typename U>
        friend double interClusterDistance(const Cluster<U> &c1, const Cluster<U> &c2);
        
        int getClusterEdges() const
        {return (m_Size * (m_Size - 1) / 2);};
        
        template <typename U>
        friend int getInterClusterEdges(const Cluster<U> &c1, const Cluster<U> &c2)
        {return ((c1.m_Size + c2.m_Size) * (c1.m_Size + c2.m_Size - 1)) / 2;};
        
        class Move
        {
        private:
            Cluster *m_To;
            Cluster *m_From;
            Point<T> *m_Point;
            
            //Constructor taking const Point p, const Cluster &from, Cluster &to
        public:
            Move() = delete;
            Move(Point<T> &p, Cluster *from, Cluster *to) :
            m_To(to),
            m_From(from),
            m_Point(p)
            {}
            
            //Method perform() which invokes c1.add(c2.remove(ptr))
            void perform()
            {
                m_To->add(*m_Point);
                m_From->remove(*m_Point);
                m_From->m_Centroid_Valid = false;
                m_To->m_Centroid_Valid = false;
            };
            
        };
        
    };
}

#include "cluster.cpp"

#endif /* defined(__pa4_ucd2312__Cluster__) */
