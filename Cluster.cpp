//
//  Cluster.cpp
//  pa4_ucd2312
//
//  Created by Tisha Konz on 10/29/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "Cluster.h"

namespace Clustering {
    
    template <typename T>
    unsigned int Cluster<T>::m_IdGenerator = 0;
    
    template <typename T>
    Cluster<T>::Cluster(const Cluster<T> &c) : m_Centroid(c.m_Dimensionality)
    {
        if (this == &c)
        {
            return;
        }
        this->m_Size = 0;
        
        if (c.m_Size == 0)
        {
            this->m_Dimensionality = c.m_Dimensionality;
            std::cout << "Creating Empty Cluster\n";
        }
        this->m_Points.assign(c.m_Points.begin(), c.m_Points.end());
        this->m_Size = c.m_Size;
        this->m_Id = c.m_Id;
    }
    
    template <typename T>
    Cluster<T>& Cluster<T>::operator=(const Cluster<T> &c)
    {
        if (this == &c)
        {
            return *this;
        }
        
        if (c.m_Size == 0)
        {
            m_Size = 0;
            return *this;
        }
        
        if (this->m_Size!= 0 && this->m_Size != c.m_Size)
        {
            
            m_Points.clear();
            
            auto it = c.m_Points.begin();
            auto thisIt = m_Points.begin();
            m_Points.push_front(*it);
            while (it != c.m_Points.end())
            {
                m_Points.insert_after(++thisIt, *++it);
                it = ++it;
            }
        }
        return *this;
    }
    
    template <typename T>
    void Cluster<T>::add(const Point<T> &value)
    {
        if (m_Size == 0)  // if there isn't a point this adds the first one
        {
            m_Size++;
            m_Points.push_front(value);
            m_Centroid_Valid = false;
            return;
            
        }
        auto it = m_Points.begin();
        auto prev = m_Points.begin();
        for (it = m_Points.begin(); it != m_Points.end(); it++)
        {
            if (value == *it)
                return;
            if (value < *it)
            {
                break;
            }
            prev = it;
        }
        if (it == m_Points.begin())
        {
            m_Points.push_front(value);
            m_Size++;
            m_Centroid_Valid = false;
        }
        else
        {
            m_Points.insert_after(std::prev, value);
            m_Size++;
            m_Centroid_Valid = false;
        }
        
    }
    
    template <typename T>
    void Cluster<T>::remove(const Point<T> &value) // greatest to least
    {
        if (m_Size == 0) // if list is empty
            return;
        if (value == *m_Points.begin()) // determine if first node is the one
        {
            m_Points.pop_front();
            m_Size--;
            m_Centroid_Valid = false;
            return;
        }
        else
        {
            auto it = m_Points.begin();
            while (it != m_Points.end() && value != *it)
            {
                it = ++it;
            }
            if (it != m_Points.end())
            {
                std::cout << *it << endl;
                m_Points.remove(*it);
                m_Size--;
                m_Centroid_Valid = false;
            }
        }
    }
    
    template <typename T>
    bool operator==(const Cluster<T> &lhs, const Cluster<T> &rhs)
    {
        if (lhs.m_Size != rhs.m_Size)
            return false;
        else
        {
            auto itL = lhs.m_Points.begin();
            auto itR = rhs.m_Points.begin();
            
            while (itL != lhs.m_Points.end() && itR != rhs.m_Points.end())
            {
                if (*itL != *itR)
                    return false;
                else
                {
                    itL = ++itL;
                    itR = ++itR;
                }
            }
            return true;
        }
    }
    
    template <typename T>
    Cluster<T>& Cluster<T>::operator+=(const Cluster<T> &rhs)
    {
        auto it = rhs.m_Points.begin();
        while (it != rhs.m_Points.end())
        {
            this->add(*it);
            it = ++it;
        }
        return *this;
    }
    
    template <typename T>
    Cluster<T> & Cluster<T>::operator-=(const Cluster<T> &rhs)
    {
        auto itR = rhs.m_Points.begin();
        auto itL =  m_Points.begin();
        while (itR != rhs.m_Points.end())
        {
            if (*itR == *itL)
            {
                this->remove(*itR);
                itR = ++itR;
                itL = ++itL;
            }
        }
        return *this;
    }
    
    template <typename T>
    Cluster<T>& Cluster<T>::operator+=(const Point<T> &rhs)
    {
        this->add(rhs);
        return *this;
    }
    
    template <typename T>
    Cluster<T> & Cluster<T>::operator-=(const Point<T> &rhs)
    {
        Point<T> p = rhs;
        this->remove(p);
        return *this;
    }
    
    template <typename T>
    const Cluster<T> operator+(const Cluster<T> &lhs, const Cluster<T> &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster<T> total = Cluster<T>(dimensions);
        
        total += lhs;
        total += rhs;
        return total;
    }
    
    template <typename T>
    const Cluster<T> operator-(const Cluster<T> &lhs, const Cluster<T> &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster<T> total = Cluster<T>(dimensions);
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    template <typename T>
    const Cluster<T> operator+(const Cluster<T> &lhs, const Point<T> &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster<T> total = Cluster<T>(dimensions);
        total += lhs;
        total += rhs;
        return total;
    }
    
    template <typename T>
    const Cluster<T> operator-(const Cluster<T> &lhs, const Point<T> &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster<T> total = Cluster<T>(dimensions);
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    template <typename T>
    Point<T>& Cluster<T>::operator[](int index)
    {
        auto it = m_Points.begin();
        if (m_Size == 0)
            return m_Centroid;
        if (index == 0)
            return *it;
        while (it != m_Points.end() && *it < index)
        {
            if (index == *it)
                return *it;
            it = ++it;
        }
        return *m_Points.end();
    }
    
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Cluster<T> &c)
    {
        if (c.m_Size != 0)
        {
            auto it = c.m_Points.begin();
            while (it != c.m_Points.end())
            {
                os << *it << " : " << c.get_id() << endl;
                it = ++it;
            }
        }
        else
        {
            os << "Empty Cluster";
            os << " : " << c.get_id() << endl;
        }
        
        return os;
    }
    
    template <typename T>
    std::istream &operator>>(std::istream &is, Cluster<T> &c)
    {
        
        string line;
        getline(is, line);
        
        //std::cin.ignore();
        cout << "Line: " << line << endl;
        
        stringstream lineStream(line);
        Point<T> *p = new Point<T>(2);
        
        lineStream >> *p;
        c.add(*p);
        
        return is;
    }
    
    template <typename T>
    void Cluster<T>::pickPoints(int k, std::vector<Point<T>> &pointVec)
    {
        //IF k >= Size
        //IF
        
        auto it = m_Points.begin();
        // put first point in pointVec[index]
        pointVec.push_back(*it) ;
        
        //m_Centroid = pointArray[0];
        
        //cout << "centroid is set to: " << m_Centroid << std::endl;
        
        int step = (m_Size / k);
        
        int index = 1;
        while(it != m_Points.end() && index < k)
        {
            int counter = step;
            while (counter != 0)
            {
                it = ++it;
                counter--;
            }
            
            pointVec.push_back(*it);
            //m_Centroid = pointArray[index];
            //cout << "set centroid: " << m_Centroid << std::endl;
            
            index++;
            
        }
    }
    
    template <typename T>
    Point<T> & Cluster<T>::compute_centroid(Cluster<T> &head)
    {
        auto it = head.m_Points.begin();
        
        //if the linked list isn't empty and if the linked list isn't just size 1 (have seperate code to deal with those)
        if (head.m_Size == 0)
        {
            m_Centroid_Valid=false;
            return *it;
            
        }
        if (head.m_Size == 1)
        {
            std::cout << "new centroid = " << m_Centroid << endl;
            m_Centroid_Valid = true;
            return m_Centroid;
        }
        
        while (it != head.m_Points.end())
        {
            m_Centroid += *it / m_Size;
            it = ++it;
        }
        std::cout << "new centroid = " << m_Centroid << endl;
        m_Centroid_Valid = true;
        return m_Centroid;
    }
    
    template <typename T>
    void Cluster<T>::makeCentroid()
    {
        m_Centroid.setDimensionality(m_Dimensionality);
    }
    
    template <typename T>
    const Point<T> Cluster<T>::get_centroid()
    {
        return m_Centroid;
    }
    //void set_centroid(Point &)
    
    template <typename T>
    void Cluster<T>::set_centroid(Point<T> &p)
    {
        
        m_Centroid =  p;
        m_Centroid_Valid = true;
    }
    
    
    // Hashing Table we have unique ID for each point
    template <typename T>
    double Cluster<T>::intraClusterDistance() const
    {
        auto it = m_Points.begin();
        auto itNext = ++m_Points.begin();
        
        double sum = 0;
        if (m_Size == 0)
        {
            return 0;
        }
        
        while(itNext != m_Points.end())
        {
            while (it != m_Points.end() && itNext != m_Points.end())
            {
                
                sum += (*it).distanceTo(*itNext);
                itNext = ++itNext;
            }
        }
        if (this->getClusterEdges() == 0)
            return sum / 2;
        double d = ((sum / 2) / this->getClusterEdges());
        
        return d;
    }
    
    template <typename T>
    double interClusterDistance(const Cluster<T> &c1, const Cluster<T> &c2)
    {
        auto itc1 = c1.m_Points.begin();
        auto itc2 = c2.m_Points.begin();
        
        if (c1.m_Size == 0 || c2.m_Size == 0)
        {
            return 0;
        }
        
        double sum = 0;
        
        while (itc1 != c1.m_Points.end() && itc2 != c2.m_Points.end())
        {
            sum += (*itc1).distanceTo(*itc2);
            itc1 = ++itc1;
            itc2 = ++itc2;
        }
        if (getInterClusterEdges(c1, c2) == 0)
            return sum / 1;
        double d = (sum / getInterClusterEdges(c1, c2));
        
        return d;
    }
    
    
}