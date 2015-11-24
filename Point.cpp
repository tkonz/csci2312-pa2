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
    template <typename T>
    unsigned int Point<T>::m_IdGenerator = 0;
    
    template <typename T>
    Point<T>::Point(const Point<T> &p)
    {
        this->m_Dimensionality = p.m_Dimensionality;
        for (auto it = p.m_Values.begin(); it != p.m_Values.end(); ++it)
        {
            m_Values.push_back(*it);
        }
        this->m_Id = p.m_Id;
    }
    
    template <typename T>
    void Point<T>::setDimensionality(unsigned n)
    {
        m_Dimensionality = n;
    }
    
    template <typename T>
    void Point<T>::setValue(int dimension, T p)
    {
        this->m_Dimensionality = dimension;
        m_Values.push_back(p);
    }
    
    template <typename T>
    T Point<T>::getValue(int dimension) const
    {
        return m_Values[dimension-1];
    }
    
    template <typename T>
    Point<T>& Point<T>::operator=(const Point<T> &p)
    {
        if (this == &p)
            return *this;
        if (this->m_Dimensionality != p.m_Dimensionality)
        {
            this->m_Dimensionality = p.m_Dimensionality;
            
        }
        
        this->m_Id = p.m_Id;
        
        for (auto it = p.m_Values.begin(); it != p.m_Values.end(); ++it)
        {
            m_Values.push_back(*it);
        }
        return *this;
        
    }
    
    template <typename T>
    Point<T>& Point<T>::operator*=(T scalar)
    {
        for (auto it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            m_Values[*it] *= scalar;
        }
        return *this;
    }
    
    template <typename T>
    Point<T>& Point<T>::operator/=(T scalar)
    {
        for (auto it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            m_Values[*it] /= scalar;
        }
        return *this;
    }
    
    template <typename T>
    const Point<T> Point<T>::operator*(T scalar) const
    {
        double product = 0;
        Point temp(m_Dimensionality);
        for (auto it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            product = *it * scalar;
            temp.setValue(*it, product);
        }
        return temp;
    }
    
    template <typename T>
    const Point<T> Point<T>::operator/(T scalar) const
    {
        double quotient = 0;
        Point temp(m_Dimensionality);
        for (auto it = m_Values.begin(); it != m_Values.end(); ++it)
        {
            quotient = *it / scalar;
            temp.setValue(*it, quotient);
        }
        return temp;
    }
    
    template <typename T>
    double Point<T>::distanceTo(const Point<T> &p) const
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
    
    template <typename T>
    Point<T> &operator+=(Point<T> & p, const Point<T> &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            p.m_Values[i] += q.m_Values[i];
        }
        return p;
    }
    
    template <typename T>
    Point<T> &operator-=(Point<T> &p, const Point<T> &q)
    {
        // check dimensions ==
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            p.m_Values[i] -= q.m_Values[i];
        }
        return p;
    }
    
    template <typename T>
    const Point<T> operator+(const Point<T> &p, const Point<T> &q)
    {
        Point<T> temp(p.m_Dimensionality);
        
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            double sum;
            sum = p.m_Values[i] + q.m_Values[i];
            temp.m_Values.push_back(sum);
        }
        return temp;
    }
    
    template <typename T>
    const Point<T> operator-(const Point<T> &p, const Point<T> &q)
    {
        // check dimensions ==
        
        Point<T> temp(p.m_Dimensionality);
        for (int i = 0; i < p.m_Dimensionality; i++)
        {
            double difference;
            difference = p.m_Values[i] - q.m_Values[i];
            temp.m_Values.push_back(difference);
        }
        return temp;
    }
    
    template <typename T>
    bool operator==(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    bool operator!=(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    bool operator<(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    bool operator>(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    bool operator<=(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    bool operator>=(const Point<T> &p, const Point<T> &q)
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
    
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Point<T> &p)
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
    
    template <typename T>
    std::istream &operator>>(std::istream &is, Point<T> &p)
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

