//
//  Point.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/17/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "point.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

namespace Clustering
{
    
    Point::Point(unsigned int dimensions)
    {
        __dimensionality = dimensions;
        values = new double[dimensions];
    }
    
    Point::Point(const Point &p)
    {
        this->__dimensionality = p.getDimensions();
        values = new double[__dimensionality];
        for (int i = 0; i < __dimensionality; i++)
        {
            values[i] = p.values[i];
        }
    }
    void Point::setDimensionality(unsigned n)
    {
        __dimensionality = n;
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
        
        if (this->__dimensionality != p.__dimensionality)
        {
            delete [] values;
            values = new double[p.__dimensionality];
        }
        //        if (!dim)
        //            dim = p.dim;
        for (int i = 0; i < p.__dimensionality; i++)
        {
            values[i] = p.values[i];
            
        }
        
        return *this;
    }
    
    Point::~Point()
    {
        delete [] values;
        //cout << "Entered Point destructor";
    }
    
    Point& Point::operator*=(double scalar)
    {
        for (int i = 0; i < __dimensionality; i++)
        {
            values[i] *= scalar;
        }
        return *this;
    }
    
    Point& Point::operator/=(double scalar)
    {
        for (int i = 0; i < __dimensionality; i++)
        {
            values[i] /= scalar;
        }
        return *this;
    }
    
    const Point Point::operator*(double scalar) const
    {
        for (int i = 0; i < __dimensionality; i++)
        {
            values[i] *= scalar;
        }
        return *this;
    }
    
    const Point Point::operator*(const Point &p)
    {
        double product = 0;
        Point temp(p.__dimensionality);
        for (int i = 0; i < p.__dimensionality; i++)
        {
            product = this->values[i] * p.values[i];
            temp.setValue(i+1, product);
        }
        return temp;
    }
    
    const Point Point::operator/(double scalar) const
    {
        
        for (int i = 0; i < __dimensionality; i++)
        {
            values[i] /= scalar;
        }
        return *this;
    }
    
    
    double Point::distanceTo(const Point &p) const
    {
        double sum;
        if (p.__dimensionality == __dimensionality)
            for (int i = 0; i < __dimensionality; i++)
            {
                double difference = values[i] - p.values[i];
                sum += difference * difference;
            }
        return sqrt(sum);
        
    }
    
    Point &operator+=(Point & p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.__dimensionality; i++)
        {
            p.values[i] += q.values[i];
        }
        return p;
    }
    
    Point &operator-=(Point &p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.__dimensionality; i++)
        {
            p.values[i] -= q.values[i];
        }
        return p;
    }
    
    const Point operator+(const Point &p, const Point &q)
    {
        
        Point temp(p.__dimensionality);
        for (int i = 0; i < p.__dimensionality; i++)
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
        
        Point temp(p.__dimensionality);
        for (int i = 0; i < p.__dimensionality; i++)
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
            for (int i = 0; i < p.__dimensionality; i++)
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
            
            for (int i = 0; i < p.__dimensionality; i++)
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
        bool lessThan = false;
        if (p.__dimensionality != q.__dimensionality)
        {
            return 0;
        }
        
        for (int i = 0; i < p.__dimensionality; i++)
        {
            if (p.values[i] > q.values[i])
            {
                lessThan = false;
                break;
                
            }
            else if(p.values[i] < q.values[i])
            {
                lessThan = true;
                break;
            }
        }
        return lessThan;
    }
    
    bool operator>(const Point &p, const Point &q)
    {
        bool greaterThan = false;
        if (p.__dimensionality == q.__dimensionality)
        {
            greaterThan = true;
        }
        
        for (int i = 0; i < p.__dimensionality; i++)
        {
            if (p.values[i] > q.values[i])
            {
                greaterThan = true;
                break;
            }
            if (p.values[i] < q.values[i])
            {
                greaterThan = false;
                break;
            }
        }
        return greaterThan;
    }
    
    bool operator<=(const Point &p, const Point &q)
    {
        bool equal = false;
        if (p.__dimensionality == q.__dimensionality)
        {
            for (int i = 0; i < p.__dimensionality; i++)
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
        if (p.__dimensionality == q.__dimensionality)
        {
            for (int i = 0; i < p.__dimensionality; i++)
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
        //os << "(";
        if (p.values)
        {
            cout << std::fixed << std::setprecision(1);
            for (int index = 0; index < p.__dimensionality; index++)
            {
                
                os << p.values[index];
                if (index == (p.__dimensionality-1))
                {
                    //os << endl;
                    
                }
                else
                {
                    os << ", ";
                }
            }
            //os << std::endl;
        }
        return os;
        
    }
    
    std::istream &operator>>(std::istream &is, Point &p)
    {
        
        string value;
        double d;
        
        int i = 1;
        while (getline(is, value, ','))
        {
            d = stod(value);
            p.setValue(i++, d);
            cout << "Value: " << d << endl;
            
        }
        
        
        return is;
        
    }
    
}
