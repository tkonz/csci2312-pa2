//
//  Point.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "point.h"
#include <cmath>

namespace Clustering
{
    
    Point::Point(int dimensions)
    {
        dim = dimensions;
        values = new double[dimensions];
    }
    
    Point::Point(const Point &p)
    {
        this->dim = p.getDimensions();
        values = new double[dim];
        for (int i = 0; i < dim; i++)
        {
            values[i] = p.values[i];
        }
    }
    
    void Point::setValue(int dimension, double p)
    {
        values[dimension - 1] = p;
    }
    
    double Point::getValue(int dimension) const
    {
        return values[dimension-1];
    }
    
    Point& Point::operator=(const Point &p)
    {
        // check for self-assignment
        if (this == &p)
            return *this;
        
        if (this->dim != p.dim)
        {
            delete [] values;
            values = new double[p.dim];
        }
        
        this->dim = p.dim;
        for (int i = 0; i < p.dim; i++)
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
        for (int i = 0; i < dim; i++)
        {
            values[i] *= scalar;
        }
        return *this;
    }
    
    const Point Point::operator*(const Point &p)
    {
        double product = 0;
        Point temp(p.dim);
        for (int i = 0; i < p.dim; i++)
        {
            product = this->values[i] * p.values[i];
            temp.setValue(i+1, product);
        }
        return temp;
    }
    
    const Point Point::operator/(double scalar) const
    {
        
        for (int i = 0; i < dim; i++)
        {
            values[i] /= scalar;
        }
        return *this;
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
        
        Point temp(p.dim);
        for (int i = 0; i < p.dim; i++)
        {
            double sum;
            sum = p.values[i] + q.values[i];
            temp.values[i] = sum;
        }
        return temp;
    }
    
    const Point operator-(const Point &p, const Point &q)
    {
        // check dimensions ==
        
        Point temp(p.dim);
        for (int i = 0; i < p.dim; i++)
        {
            double difference;
            difference = p.values[i] - q.values[i];
            temp.values[i] = difference;
        }
        return temp;
    }
    
    bool operator==(const Point &p, const Point &q)
    {
        bool equal = false;
        //std::cout << "bool = " << equal << std::endl;
        if (p.getDimensions() == q.getDimensions())
        {
            bool equal = true;
            //std::cout << "bool = " << equal << std::endl;
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] == q.values[i])
                {
                    equal = true;
                    //std::cout << "bool = " << equal << std::endl;
                }
                else
                {
                    
                    equal = false;
                }
            }
            return equal;
        }
        return equal;
    }
    
    bool operator!=(const Point &p, const Point &q)
    {
        bool notEqual = true;
        if (p.getDimensions() == q.getDimensions())
        {
            
            for (int i = 0; i < p.dim; i++)
            {
                if (p.values[i] == q.values[i])
                {
                    notEqual = false;
                    
                }
                else
                {
                    notEqual = true;
                }
            }
            return notEqual;
        }
        return notEqual;
    }
    
    bool operator<(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.dim == q.dim)
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
        if (p.dim > q.dim)
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
        if (p.dim == q.dim)
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
        if (p.dim == q.dim)
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
        for (int index = 0; index < p.dim; index++)
        {
            
            os << p.values[index];
            if (index == (p.dim-1))
            {
                os << ")\n";
            }
            else
            {
                os << ", ";
            }
        }
        //os << std::endl;
        return os;
    }
    
    std::istream &operator>>(std::istream &is, Point &p)
    {
        
        for (int i = -1; i < p.dim; i++)
        {
            is >> p.values[i];
        }
        return is;
    }
    
}
