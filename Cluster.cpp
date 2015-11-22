//
//  Cluster.cpp
//  pa4_ucd2312
//
//  Created by Tisha Konz on 10/29/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "Cluster.h"

namespace Clustering {
    
    unsigned int Cluster::m_IdGenerator = 0;
    
    Cluster::Cluster(const Cluster &c) : m_Centroid(c.m_Dimensionality)
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
    
    
    Cluster& Cluster::operator=(const Cluster &c)
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
            
            std::forward_list<Point>::const_iterator it = c.m_Points.begin();
            std::forward_list<Point>::iterator thisIt = m_Points.begin();
            m_Points.push_front(*it);
            while (it != c.m_Points.end())
            {
                m_Points.insert_after(++thisIt, *++it);
                it = ++it;
            }
        }
        return *this;
    }
    
    void Cluster::add(const Point &value)
    {
        if (m_Size == 0)  // if there isn't a point this adds the first one
        {
            m_Size++;
            m_Points.push_front(value);
            m_Centroid_Valid = false;
            return;
            
        }
        std::forward_list<Point>::const_iterator it;
        std::forward_list<Point>::const_iterator prev = m_Points.begin();
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
            m_Points.insert_after(prev, value);
            m_Size++;
            m_Centroid_Valid = false;
        }
        
    }
    
    void Cluster::remove(const Point &value) // greatest to least
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
            std::forward_list<Point>::const_iterator it = m_Points.begin();
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
    
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        if (lhs.m_Size != rhs.m_Size)
            return false;
        else
        {
            std::forward_list<Point>::const_iterator itL = lhs.m_Points.begin();
            std::forward_list<Point>::const_iterator itR = rhs.m_Points.begin();
            
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
    
    Cluster& Cluster::operator+=(const Cluster &rhs)
    {
        std::forward_list<Point>::const_iterator it = rhs.m_Points.begin();
        while (it != rhs.m_Points.end())
        {
            this->add(*it);
            it = ++it;
        }
        return *this;
    }
    
    Cluster & Cluster::operator-=(const Cluster &rhs)
    {
        std::forward_list<Point>::const_iterator itR = rhs.m_Points.begin();
        std::forward_list<Point>::iterator itL =  m_Points.begin();
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
    
    Cluster& Cluster::operator+=(const Point &rhs)
    {
        this->add(rhs);
        return *this;
    }
    
    Cluster & Cluster::operator-=(const Point &rhs)
    {
        Point p = rhs;
        this->remove(p);
        return *this;
    }
    
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster total = Cluster(dimensions);
        
        total += lhs;
        total += rhs;
        return total;
    }
    
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster total = Cluster(dimensions);
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    const Cluster operator+(const Cluster &lhs, const Point &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster total = Cluster(dimensions);
        total += lhs;
        total += rhs;
        return total;
    }
    
    const Cluster operator-(const Cluster &lhs, const Point &rhs)
    {
        unsigned dimensions = lhs.m_Dimensionality;
        Cluster total = Cluster(dimensions);
        total -= lhs;
        total -= rhs;
        return total;
    }
    
    Point& Cluster::operator[](int index)
    {
        std::forward_list<Point>::iterator it = m_Points.begin();
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
    
    //    std::forward_list<Point>::iterator Cluster::operator[](int index)
    //    {
    //        std::forward_list<Point>::iterator it = m_Points.begin();
    //        if (index == 0)
    //            return it;
    //        while (it != m_Points.end() && *it < index)
    //        {
    //            if (index == *it)
    //                return it;
    //            it = ++it;
    //        }
    //        return m_Points.end();
    //    }
    //
    
    std::ostream &operator<<(std::ostream &os, const Cluster &c)
    {
        if (c.m_Size != 0)
        {
            std::forward_list<Point>::const_iterator it = c.m_Points.begin();
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
    
    std::istream &operator>>(std::istream &is, Cluster &c)
    {
        
        string line;
        getline(is, line);
        
        //std::cin.ignore();
        cout << "Line: " << line << endl;
        
        stringstream lineStream(line);
        Point *p = new Point(2);
        
        lineStream >> *p;
        c.add(*p);
        
        return is;
    }
    
    void Cluster::pickPoints(int k, std::vector<Point> &pointVec)
    {
        //IF k >= Size
        //IF
        
        std::forward_list<Point>::iterator it = m_Points.begin();
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
    
    Point & Cluster::compute_centroid(Cluster &head)
    {
        std::forward_list<Point>::iterator it = head.m_Points.begin();
        
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
    
    void Cluster::makeCentroid()
    {
        m_Centroid.setDimensionality(m_Dimensionality);
    }
    
    const Point Cluster::get_centroid()
    {
        return m_Centroid;
    }
    
    void Cluster::set_centroid(Point &p)
    {
        
        m_Centroid =  p;
        m_Centroid_Valid = true;
    }
    
    
    // Hashing Table we have unique ID for each point
    double Cluster::intraClusterDistance() const
    {
        std::forward_list<Point>::const_iterator it = m_Points.begin();
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
    
    double interClusterDistance(const Cluster &c1, const Cluster &c2)
    {
        std::forward_list<Point>::const_iterator itc1 = c1.m_Points.begin();
        std::forward_list<Point>::const_iterator itc2 = c2.m_Points.begin();
        
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