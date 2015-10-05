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

namespace Clustering {
    
    class Point {
    private:
        int dim;        // number of dimensions of the point
        double *values; // values of the point's dimensions
        
    public:
        Point(int);
        
        
        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();
        
        // Accessors & mutators
        int getDimensions() const { return dim; }
        void setValue(int, double);
        double getValue(int) const;
        
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

