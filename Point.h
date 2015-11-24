//
//  point.h
//  pa4_ucd2312
//
//  Created by Tisha Konz on 10/29/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

//// friend functions need foward declaration
// template <typename T> class Point;
// template <typename T> std::ostream &operator<<(std::ostream &os, const Point<T> &p);
// template <typename T> bool operator <(const Point<T> &rhs, const Point<T> &lhs);
//
// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

namespace Clustering {
    template <typename T>
    class Point {
    private:
        unsigned int m_Dimensionality;        // number of dimensions of the point
        unsigned int m_Id;
        static unsigned int m_IdGenerator;
        
        std::vector<T> m_Values; // values of the point's dimensions WILL BECOME vector<T> __values;
        
    public:
        //Point :  __dimensionality(dim), m_values(__dimensions) {};
        Point(unsigned int dim) :
        m_Dimensionality(dim),
        m_Id(m_IdGenerator++)
        {};
        
        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        
        
        // Accessors & mutators
        int getDimensions() const { return m_Dimensionality; }
        void setDimensionality(int d) {m_Dimensionality = d;}
        void setValue(int, T);
        T getValue(int) const;
        void setDimensionality(unsigned);
        unsigned int getId() const {return m_Id;}
        // Functions
        double distanceTo(const Point &) const;
        
        // Overloaded operators
        
        
        // Members
        Point &operator*=(T);
        Point &operator/=(T);
        const Point operator*(T) const; // prevent (p1*2) = p2;
        const Point operator/(T) const;
        
        
        double &operator[](int index) { return m_Values[index - 1]; } // TODO out-of-bds?
        
        // Friends
        template <typename S>
        friend Point<S> &operator+=(Point<S> &, const Point<S> &);
        
        template <typename S>
        friend Point<S> &operator-=(Point<S> &, const Point<S> &);
        
        template <typename S>
        friend const Point<S> operator+(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend const Point<S> operator-(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator==(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator!=(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator<(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator>(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator<=(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend bool operator>=(const Point<S> &, const Point<S> &);
        
        template <typename S>
        friend std::ostream &operator<<(std::ostream &, const Point<S> &);
        
        template <typename S>
        friend std::istream &operator>>(std::istream &, Point<S> &);
        
    };
    
}

#include "point.cpp"

#endif //CLUSTERING_POINT_H

