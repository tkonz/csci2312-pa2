//
//  point.cpp
//  pa4_ucd2312
//
//  Created by Tisha Konz on 10/29/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//


#include "point.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

namespace Clustering
{
    unsigned int Point::m_IdGenerator = 0;
    
    Point::Point(const Point &p)
    {
        this->m_Dimensionality = p.m_Dimensionality;
        for (std::vector<double>::const_iterator it = p.m_Values.begin(); it != p.m_Values.end(); ++it)
        {
            m_Values.push_back(*it);
        }
        this->m_Id = p.m_Id;
    }
    
    void Point::setDimensionality(unsigned n)
    {
        m_Dimensionality = n;
    }
    
    void Point::setValue(int dimension, double p)
    {
        this->m_Dimensionality = dimension;
        m_Values.push_back(p);
    }
    
    double Point::getValue(int dimension) const
    {
        return m_Values[dimension-1];
    }
    
    
    Point& Point::operator=(const Point &p)
    {
        if (this == &p)
            return *this;
        if (this->m_Dimensionality != p.m_Dimensionality)
        {
            this->m_Dimensionality = p.m_Dimensionality;
            
        }
        
        this->m_Id = p.m_Id;
        
        for (std::vector<double>::const_iterator it = p.m_Values.begin(); it != p.m_Values.end(); ++it)
        {
            m_Values.push_back(*it);
        }
        
        return *this;
    }
    
    Point& Point::operator*=(double scalar)
    {
        for (std::vector<double>::iterator it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            m_Values[*it] *= scalar;
        }
        return *this;
    }
    
    Point& Point::operator/=(double scalar)
    {
        for (std::vector<double>::iterator it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            m_Values[*it] /= scalar;
        }
        return *this;
    }
    
    const Point Point::operator*(double scalar) const
    {
        double product = 0;
        Point temp(m_Dimensionality);
        for (std::vector<double>::const_iterator it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            product = *it * scalar;
            temp.setValue(*it, product);
        }
        return temp;
    }
    
    
    const Point Point::operator/(double scalar) const
    {
        double quotient = 0;
        Point temp(m_Dimensionality);
        for (std::vector<double>::const_iterator it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            quotient = *it / scalar;
            temp.setValue(*it, quotient);
        }
        return temp;
    }
    
    double Point::distanceTo(const Point &p) const
    {
        double sum = 0;
        if (p.m_Dimensionality == m_Dimensionality)
            for (int i = 0; i < m_Dimensionality; i++)
            {
                double difference = 0;
                difference = m_Values[i] - p.m_Values[i];
                sum += difference * difference;
            }
        return sqrt(sum);
        
    }
    
    Point &operator+=(Point & p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            p.m_Values[i] += q.m_Values[i];
        }
        return p;
    }
    
    Point &operator-=(Point &p, const Point &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            p.m_Values[i] -= q.m_Values[i];
        }
        return p;
    }
    
    const Point operator+(const Point &p, const Point &q)
    {
        
        Point temp(p.m_Dimensionality);
        
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            double sum;
            sum = p.m_Values[i] + q.m_Values[i];
            temp.m_Values.push_back(sum);
        }
        return temp;
    }
    
    const Point operator-(const Point &p, const Point &q)
    {
        // check dimensions ==
        
        Point temp(p.m_Dimensionality);
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            double difference;
            difference = p.m_Values[i] - q.m_Values[i];
            temp.m_Values.push_back(difference);
        }
        return temp;
    }
    
    
    
    bool operator==(const Point &p, const Point &q)
    {
        bool equal = false;
        //std::cout << "bool = " << equal << std::endl;
        if (p.m_Dimensionality == q.m_Dimensionality)
        {
            bool equal = true;
            //std::cout << "bool = " << equal << std::endl;
            for (int i = 0; i < p.m_Dimensionality; i++)
            {
                if (p.m_Values[i] == q.m_Values[i])
                {
                    equal = true;
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
            if (p.m_Id == q.m_Id)
            {
                notEqual = false;
            }
            for (int i = 0; i < p.m_Dimensionality; i++)
            {
                if (p.m_Values[i] == q.m_Values[i])
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
        if (p.m_Dimensionality != q.m_Dimensionality)
        {
            return 0;
        }
        
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            if (p.m_Values[i] > q.m_Values[i])
            {
                lessThan = false;
                break;
                
            }
            else if(p.m_Values[i] < q.m_Values[i])
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
        if (p.m_Dimensionality == q.m_Dimensionality)
        {
            greaterThan = true;
        }
        
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            if (p.m_Values[i] > q.m_Values[i])
            {
                greaterThan = true;
                break;
            }
            if (p.m_Values[i] < q.m_Values[i])
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
        if (p.m_Dimensionality == q.m_Dimensionality)
        {
            for (int i = 0; i < p.m_Dimensionality; i++)
            {
                if (p.m_Values[i] < q.m_Values[i] || p.m_Values[i] == q.m_Values[i])
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
        if (p.m_Dimensionality == q.m_Dimensionality)
        {
            for (int i = 0; i < p.m_Dimensionality; i++)
            {
                if (p.m_Values[i] > q.m_Values[i] || p.m_Values[i] == q.m_Values[i])
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
        if (p.m_Values.size() != 0)
        {
            cout << std::fixed << std::setprecision(1);
            for (std::vector<double>::const_iterator it = p.m_Values.begin(); it != p.m_Values.end(); ++it)
            {
                os << *it;
                if (it == --p.m_Values.end())
                {
                    //os << endl;
                }
                else
                {
                    os << ", ";
                }
            }
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

