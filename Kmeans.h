//
//  Kmeans.h
//  pa2-ucd
//
//  Created by Tisha Konz on 10/9/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#ifndef __pa2_ucd__Kmeans__
#define __pa2_ucd__Kmeans__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "cluster.h"
#include "point.h"

namespace Clustering
{
    template <typename T>
    class Kmeans
    {
    private:
        int m_k;
        double oldScore, newScore;
        double scoreDiff;
        static double SCORE_DIFF_THRESHOLD;
        int __dimensionality;
        Cluster<T> point_space;
        std::vector <Cluster<T>> clusterVec;
        
    public:
        Kmeans(int k, int dim) :
        m_k(k),
        __dimensionality(dim),
        // initial cluster called point_space initialized in Kmeans constructor
        point_space(__dimensionality)
        {
            ifstream csv("points.txt");
            
            while (csv.is_open() && !csv.eof())
            {
                csv >> point_space;
                cout << "Point: " << point_space << endl;
                
            }
            cout << "Point: " << point_space << endl;
            //cout << point_space.get_Size();
            csv.close();
            
        };
        void initializeCentroids();
        void initializeClusters();
        Cluster<T>* findNearestCentroid(Point<T>&);
        double computeClusteringScore();
        
        void kMeansAlgorithm();
        void printClusters();
        
    };
    
}

#include "kmeans.cpp"

#endif /* defined(__pa2_ucd__Kmeans__) */
