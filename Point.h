//
//  Point.h
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//
#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
// #include <vector>
// friend functions need foward declaration
// template <typename T, int dim> class Point;
// template <typename T, int dim> std::ostream &operator<<(std::ostream &os, const POint<T, dim> &p);
// template <typname T, int dim> bool operator <(const Point<T, dim> &rhs, const Point<T, dim> &lhs);

// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

namespace Clustering {
    
    class Point {
    private:
        unsigned int __dimensionality;        // number of dimensions of the point
        double *values; // values of the point's dimensions WILL BECOME vector<T> __values;
        
    public:
        Point(unsigned int); //Point :  -- dimensions(dim), __values(__dimensions) {};
        
        // freind std::ostream &operator<< (std::ostream &os, const Point &p) {auto it = p.__values.begin();
        // for (; it != --p.values.end(); ++it)
        //          std::cout << *it<< ", "
        //  std:: cout << *it;
        // return os;
        //}
        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();
        
        
        // Accessors & mutators
        int getDimensions() const { return __dimensionality; }
        //void setDimensionality(int d) {dim = d;}
        void setValue(int, double);
        double getValue(int) const;
        void setDimensionality(unsigned);
        // Functions
        double distanceTo(const Point &) const;
        
        // Overloaded operators
        
        // Members
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1*2) = p2;
        const Point operator*(const Point &);
        const Point operator/(double) const;
        
        double &operator[](int index) { return values[index - 1]; } // TODO out-of-bds?
        
        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);
        
        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);
        
        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);
        
        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };
    
}
#endif //CLUSTERING_POINT_H

