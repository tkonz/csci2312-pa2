//
//  Point.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "Point.h"
#include <cmath>

namespace Clustering
{

    Point::Point(int dimensions)
    {
        values = new double[dimensions];
    }
    
    Point::Point(const Point &p)
    {
        values = new double[p.dim];
        for (int i = 0; i < dim; i++)
        {
            values[i] = p.values[i];
        }
    }

    void Point::setValue(int dimension, double p)
    {
         values[dimension] = p;
    }
    
    double Point::getValue(int dimension) const
    {
        return values[dimension];
    }

    Point& Point::operator=(const Point &p)
    {
        // check for self-assignment
        if (dim != p.dim)
        {
            delete [] values;
            values = new double[p.dim];
        }
        
        dim = p.dim;
        for (int i = 0; i < dim; i++)
        {
            values[i] = p.values[i];
            
        }
        return *this;
    }
    
    Point::~Point()
    {
        delete [] values;
    }
    
    Point& Point::operator*=(double scalar)
    {
        for (int i = 0; i < dim; i++)
        {
            values[i] *= scalar;
        }
        return *this;
    }
    
    Point& Point::operator/=(double scalar)
    {
        for (int i = 0; i < dim; i++)
        {
            values[i] /= scalar;
        }
        return *this;
    }
    
    const Point Point::operator*(double scalar) const
    {
        return Point(dim) *= scalar;
    }
    
    const Point Point::operator*(const Point &p)
    {
        for (int i = 0; i < dim; i++)
        {
            Point(dim) = values[i] * values[i];
        }
        return *this;
    }
    
    const Point Point::operator/(double scalar) const
    {
        return Point(dim) /= scalar;
    }
    
    
    double Point::distanceTo(const Point &p) const
    {
        double sum;
        if (p.dim == dim)
           for (int i = 0; i < dim; i++)
           {
               double difference = values[i] - p.values[i];
               sum += difference * difference;
           }
        return sqrt(sum);
    }
    
    
    Point &operator+=(Point & p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.dim; i++)
        {
            p.values[i] += q.values[i];
        }
        return p;
    }
    
    Point &operator-=(Point &p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.dim; i++)
        {
            p.values[i] -= q.values[i];
        }
        return p;
    }
    
    const Point operator+(const Point &p, const Point &q)
    {
        // check dimensions ==
        Point *temp = new Point(p.dim);
        for (int i = 0; i < p.dim; i++)
        {
            temp[i] = p.values[i] + q.values[i];
        }
        return *temp;
    }
    
    const Point operator-(const Point &p, const Point &q)
    {
        // check dimensions ==
        
        Point *temp = new Point(p.dim);
        for (int i = 0; i < p.dim; i++)
        {
            temp[i] = p.values[i] - q.values[i];
        }
        return *temp;
    }
    
    bool operator==(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() == q.getDimensions())
        {
            bool equal = true;
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] != q.values[i])
                {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }
    
    bool operator!=(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() == q.getDimensions())
        {
            
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] != q.values[i])
                {
                    equal = true;
                    break;
                }
            }
        }
        return equal;
    }
    
    bool operator<(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() == q.getDimensions())
        {
            equal = true;
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] > q.values[i])
                {
                    equal = false;
                    break;
                }
                
            }
        }
        return equal;
    }
    
    bool operator>(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() > q.getDimensions())
        {
            equal = true;
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] > q.values[i])
                {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }
    
    bool operator<=(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() == q.getDimensions())
        {
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] < q.values[i] || p.values[i] == q.values[i])
                {
                    equal = true;
                    break;
                }
                
            }
        }
        return equal;
    }
    
    bool operator>=(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.getDimensions() == q.getDimensions())
        {
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] > q.values[i] || p.values[i] == q.values[i])
                {
                    equal = true;
                    break;
                }
                
            }
        }
        return equal;
    }



    
    std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(";
        for (int i = 0; i < (p.dim - 1); i++)
        {
            os << p.values[i] << ", ";
        }
        os << ")\n";
        return os;
    }

    std::istream &operator>>(std::istream &is, Point &p)
    {
        
        for (int i = 0; i < p.dim; i++)
        {
            is >> p.values[i];
        }
        return is;
    }

}
